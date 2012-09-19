using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace UUEditor
{
    public partial class Form1 : Form
    {
        private string tilesDir = "";
        private LinkedList<PictureBox> tileImages = new LinkedList<PictureBox>();
        private int width = 2;
        private int height = 2;
        private TileInfo[,] tiles;

        private PictureBox[,] horizontalWalls;
        private PictureBox[,] verticalWalls;

        private TileInfo selectedTile = null;
        private Dictionary<TileInfo.WallType, RadioButton> upButtons = new Dictionary<TileInfo.WallType, RadioButton>();
        private Dictionary<TileInfo.WallType, RadioButton> rightButtons = new Dictionary<TileInfo.WallType, RadioButton>();
        private Dictionary<TileInfo.WallType, RadioButton> downButtons = new Dictionary<TileInfo.WallType, RadioButton>();
        private Dictionary<TileInfo.WallType, RadioButton> leftButtons = new Dictionary<TileInfo.WallType, RadioButton>();

        Image wall_h;
        Image door_h;
        Image blastDoor_h;
        Image wall_v;
        Image door_v;
        Image blastDoor_v;

        const int maxWidth = 15;
        const int maxHeight = 15;


        public Form1()
        {
            InitializeComponent();
        }

        TileInfo.WallType getWallType(RadioButton button)
        {
            if (button.Text == "Empty") {
                return TileInfo.WallType.Empty;
            } else if (button.Text == "Wall") {
                return TileInfo.WallType.Wall;
            } else if (button.Text == "Door") {
                return TileInfo.WallType.Door;
            } else if (button.Text == "Blast Door") {
                return TileInfo.WallType.BlastDoor;
            } else {
                throw new Exception();
            }
        }

        void upClick(object sender, EventArgs e)
        {
            RadioButton button = (RadioButton)sender;
            TileInfo.WallType type = getWallType(button);
            selectedTile.up = type;
            if (selectedTile.y > 0) {
                tiles[selectedTile.x, selectedTile.y - 1].down = type;
            }
            redrawRoomTiles();
        }

        void downClick(object sender, EventArgs e)
        {
            RadioButton button = (RadioButton)sender;
            TileInfo.WallType type = getWallType(button);
            selectedTile.down = type;
            if (selectedTile.y < height - 1) {
                tiles[selectedTile.x, selectedTile.y + 1].up = type;
            }
            redrawRoomTiles();
        }

        void rightClick(object sender, EventArgs e)
        {
            RadioButton button = (RadioButton)sender;
            TileInfo.WallType type = getWallType(button);
            selectedTile.right = type;
            if (selectedTile.x < width - 1) {
                tiles[selectedTile.x+1, selectedTile.y].left = type;
            }
            redrawRoomTiles();
        }

        void leftClick(object sender, EventArgs e)
        {
            RadioButton button = (RadioButton)sender;
            TileInfo.WallType type = getWallType(button);
            selectedTile.left = type;
            if (selectedTile.x > 0) {
                tiles[selectedTile.x-1, selectedTile.y].right = type;
            }
            redrawRoomTiles();
        }

        void addHandler(RadioButton but, Panel panel)
        {
            if (panel.Name == "upPanel") {
                but.CheckedChanged += new EventHandler(upClick);
            } else if (panel.Name == "rightPanel") {
                but.CheckedChanged += new EventHandler(rightClick);
            } else if (panel.Name == "leftPanel") {
                but.CheckedChanged += new EventHandler(leftClick);
            } else if (panel.Name == "downPanel") {
                but.CheckedChanged += new EventHandler(downClick);
            } else {
                throw new Exception();
            }
        }

        private void createButtons(Dictionary<TileInfo.WallType, RadioButton> buttons, Panel panel)
        {
            RadioButton but = null;
            but = new RadioButton();
            but.Text = "Empty";
            but.Top = 0;
            buttons[TileInfo.WallType.Empty] = but;
            addHandler(but, panel);
            panel.Controls.Add(but);
            but = new RadioButton();
            but.Text = "Wall";
            but.Top = 18;
            buttons[TileInfo.WallType.Wall] = but;
            addHandler(but, panel);
            panel.Controls.Add(but);
            but = new RadioButton();
            but.Text = "Door";
            but.Top = 36;
            buttons[TileInfo.WallType.Door] = but;
            addHandler(but, panel);
            panel.Controls.Add(but);
            but = new RadioButton();
            but.Text = "Blast Door";
            but.Top = 54;
            buttons[TileInfo.WallType.BlastDoor] = but;
            addHandler(but, panel);
            panel.Controls.Add(but);
        }

        private void initializeRadioButtons()
        {
            createButtons(upButtons, upPanel);
            createButtons(leftButtons, leftPanel);
            createButtons(downButtons, downPanel);
            createButtons(rightButtons, rightPanel);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            wall_h = Bitmap.FromFile("wall_h.bmp");
            door_h = Bitmap.FromFile("door_h.bmp");
            blastDoor_h = Bitmap.FromFile("blastdoor_h.bmp");

            wall_v = Bitmap.FromFile("wall_v.bmp");
            door_v = Bitmap.FromFile("door_v.bmp");
            blastDoor_v = Bitmap.FromFile("blastdoor_v.bmp");
            initializeRadioButtons();
            currentTileBox.AllowDrop = true;
            currentTileBox.DragDrop += new DragEventHandler(pictureBox_DragDrop);
            currentTileBox.DragEnter += new DragEventHandler(pictureBox_DragEnter);
            resizeRoom();
            selectedTile = tiles[0, 0];
            selectTile(selectedTile);
        }

        private void clearTiles()
        {
            foreach (PictureBox box in tileImages) {
                tilesPanel.Controls.Remove(box);
            }
            tileImages.Clear();
        }

        private void reloadTiles()
        {
            clearTiles();
            
            if (tilesDir == "") {
                return;
            }
            string[] files = Directory.GetFiles(tilesDir, "*.bmp");
            int lastTop = 15;
            foreach (string file in files) {
                PictureBox box = new PictureBox();
                box.Width = 25;
                box.Height = 25;
                box.ImageLocation = file;
                box.Left = 10;
                box.Top = lastTop;
                tilesPanel.Controls.Add(box);
                tileImages.AddLast(box);
                string name = Path.GetFileNameWithoutExtension(file);
                box.Name = name;
                box.MouseDown += new MouseEventHandler(box_mouseDown);

                Label boxLabel = new Label();
                boxLabel.Text = name;
                boxLabel.Left = 40;
                boxLabel.Top = lastTop;
                tilesPanel.Controls.Add(boxLabel);
                lastTop += 30;
            }
        }

        private void box_mouseDown(object sender, MouseEventArgs e)
        {
            PictureBox box = (PictureBox)sender;
            box.DoDragDrop(box, DragDropEffects.Copy);
        }

        private void pictureBox_DragEnter(object sender, DragEventArgs e)
        {
            if (sender is PictureBox) {
                e.Effect = DragDropEffects.Copy;
            } else {
                e.Effect = DragDropEffects.None;
            }
        }

        private void pictureBox_DragDrop(object sender, DragEventArgs e)
        {
            PictureBox picbox = (PictureBox)e.Data.GetData("System.Windows.Forms.PictureBox");
            //PictureBox picbox = (PictureBox)sender;
            currentTileBox.ImageLocation = picbox.ImageLocation;
            selectedTile.tileBox.ImageLocation = picbox.ImageLocation;
        }

        private void setCurrentImage()
        {

        }

        private void setTilesDirButton_Click(object sender, EventArgs e)
        {
            DialogResult res = selectTilesDirDialog.ShowDialog();
            if (res != DialogResult.OK) {
                tilesDir = "";
                tilesDirLabel.Text = "No folder selected";
                return;
            }
            tilesDir = selectTilesDirDialog.SelectedPath;
            tilesDirLabel.Text = tilesDir;
            reloadTiles();
        }

        private void reloadTilesButton_Click(object sender, EventArgs e)
        {
            reloadTiles();
        }

        private void resizeButton_Click(object sender, EventArgs e)
        {
            resizeRoom();
        }

        private void roomTileClick(object sender, EventArgs e)
        {
            PictureBox box = (PictureBox)sender;
            for (int i = 0; i < width; ++i) {
                for (int j = 0; j < height; ++j) {
                    if (tiles[i, j].tileBox == box) {
                        selectTile(tiles[i, j]);
                    }
                }
            }
        }

        private void selectTile(TileInfo info)
        {
            xBox.Text = info.x.ToString();
            yBox.Text = info.y.ToString();
            currentTileBox.ImageLocation = info.tileBox.ImageLocation;
            selectedTile = info;
            upButtons[info.up].Select();
            downButtons[info.down].Select();
            rightButtons[info.right].Select();
            leftButtons[info.left].Select();
        }

        private void resizeRoom()
        {
            int x = -1;
            int y = -1;
            try {
                x = int.Parse(widthBox.Text);
                y = int.Parse(heightBox.Text);
            } catch (System.Exception) {
                return;
            }
            if (x < 1 || x > maxWidth || y < 1 || y > maxHeight) {
                return;
            }
            roomTilesPanel.Width = x * 25 + 4;
            roomTilesPanel.Height = y * 25 + 4;
            TileInfo[,] newTiles = new TileInfo[x, y];
            for (int i = 0; i < x; ++i) {
                for (int j = 0; j < y; ++j) {
                    newTiles[i, j] = new TileInfo();
                    if (i < width && j < height && tiles != null) {
                        TileInfo oldTile = tiles[i, j];
                        newTiles[i, j] = oldTile;
                        if (i == width - 1) {
                            newTiles[i, j].right = TileInfo.WallType.Empty;
                        }
                        if (j == height - 1) {
                            newTiles[i, j].down = TileInfo.WallType.Empty;
                        }
                        if (i == x - 1) {
                            newTiles[i, j].right = TileInfo.WallType.Wall;
                        }
                        if (j == y - 1) {
                            newTiles[i, j].down = TileInfo.WallType.Wall;
                        }
                    } else {
                        TileInfo newTile = new TileInfo();
                        newTile.x = i;
                        newTile.y = j;
                        newTile.tileBox = new PictureBox();
                        newTile.tileBox.Left = i * 25 + 1;
                        newTile.tileBox.Top = j * 25 + 1;
                        if (i > 0) {
                            newTile.left = newTiles[i - 1, j].right;
                        } else {
                            newTile.left = TileInfo.WallType.Wall;
                        }
                        if (i < x - 1) {
                            newTile.right = TileInfo.WallType.Empty;
                        } else {
                            newTile.right = TileInfo.WallType.Wall;
                        }
                        if (j > 0) {
                            newTile.up = newTiles[i, j - 1].down;
                        } else {
                            newTile.up = TileInfo.WallType.Wall;
                        }
                        if (j < y - 1) {
                            newTile.down = TileInfo.WallType.Empty;
                        } else {
                            newTile.down = TileInfo.WallType.Wall;
                        }
                        newTile.tileBox.Click += new EventHandler(roomTileClick);
                        newTile.tileBox.Width = 25;
                        newTile.tileBox.Height = 25;
                        newTile.tileBox.ImageLocation = "empty.bmp";
                        //newTile.tileBox.BorderStyle = BorderStyle.FixedSingle;
                        newTiles[i, j] = newTile;
                    }
                }
            }
            horizontalWalls = new PictureBox[x+1, y+1];
            verticalWalls = new PictureBox[x+1, y+1];
            for (int i = 0; i <= x; i++) {
                for (int j = 0; j <= y; j++) {
                    PictureBox horizontal = new PictureBox();
                    horizontal.Width = 25;
                    horizontal.Height = 2;
                    horizontal.Left = i * 25+1;
                    horizontal.Top = j * 25;
                    horizontalWalls[i, j] = horizontal;

                    PictureBox vertical = new PictureBox();
                    vertical.Width = 2;
                    vertical.Height = 25;
                    vertical.Left = i * 25;
                    vertical.Top = j * 25+1;
                    verticalWalls[i, j] = vertical;
                }
            }

            tiles = newTiles;
            width = x;
            height = y;
            redrawRoomTiles();
            selectTile(tiles[0, 0]);
        }

        private void drawHorizontalWall(int i, int j, TileInfo.WallType type)
        {
            switch (type) {
                case TileInfo.WallType.Wall:
                    horizontalWalls[i, j].Image = wall_h;
                    break;
                case TileInfo.WallType.Door:
                    horizontalWalls[i, j].Image = door_h;
                    break;
                case TileInfo.WallType.BlastDoor:
                    horizontalWalls[i, j].Image = blastDoor_h;
                    break;
            }
            if (type != TileInfo.WallType.Empty) {
                roomTilesPanel.Controls.Add(horizontalWalls[i, j]);
            }
        }

        private void drawVerticalWall(int i, int j, TileInfo.WallType type)
        {
            switch (type) {
                case TileInfo.WallType.Wall:
                    verticalWalls[i, j].Image = wall_v;
                    break;
                case TileInfo.WallType.Door:
                    verticalWalls[i, j].Image = door_v;
                    break;
                case TileInfo.WallType.BlastDoor:
                    verticalWalls[i, j].Image = blastDoor_v;
                    break;
            }
            if (type != TileInfo.WallType.Empty) {
                roomTilesPanel.Controls.Add(verticalWalls[i, j]);
            }
        }

        private void redrawRoomTiles()
        {
            roomTilesPanel.Controls.Clear();
            for (int i = 0; i < width; ++i) {
                for (int j = 0; j < height; ++j) {
                    TileInfo tile = tiles[i,j];
                    drawHorizontalWall(i, j, tile.up);
                    drawVerticalWall(i, j, tile.left);
                }
            }

            for (int i = 0; i < width; ++i) {
                TileInfo tile = tiles[i, height-1];
                drawHorizontalWall(i, height, tile.down);
            }
            for (int j = 0; j < height; ++j) {
                TileInfo tile = tiles[width-1, j];
                drawVerticalWall(width, j, tile.right);
            }
            for (int i = 0; i < width; ++i) {
                for (int j = 0; j < height; ++j) {
                    TileInfo tile = tiles[i, j];
                    roomTilesPanel.Controls.Add(tile.tileBox);
                }
            }
        }

        private Dictionary<string, int> mapTiles()
        {
            Dictionary<string, int> res = new Dictionary<string, int>();
            int id = 0;
            for (int i = 0; i < width; ++i) {
                for (int j = 0; j < height; ++j) {
                    string tileName = tiles[i, j].tileBox.ImageLocation;
                    tileName = Path.GetFileName(tileName);
                    if (!res.ContainsKey(tileName)) {
                        res[tileName] = id++;
                    }
                }
            }
            return res;
        }

        private byte getWallType(TileInfo.WallType type)
        {
            switch (type) {
                case TileInfo.WallType.Empty:
                    return 0;
                case TileInfo.WallType.Wall:
                    return 1;
                case TileInfo.WallType.Door:
                    return 2;
                case TileInfo.WallType.BlastDoor:
                    return 3;
            }
            throw new Exception();
        }

        private TileInfo.WallType getWallType(int type)
        {
            switch (type) {
                case 0:
                    return TileInfo.WallType.Empty;
                case 1:
                    return TileInfo.WallType.Wall;
                case 2:
                    return TileInfo.WallType.Door;
                case 3:
                    return TileInfo.WallType.BlastDoor;
            }
            return 0;
            throw new Exception();
        }

        private void saveButton_Click(object sender, EventArgs e)
        {
            DialogResult res = saveFileDialog.ShowDialog();
            if (res != DialogResult.OK) {
                return;
            }
            /*
             * UURM:4 bytes
             * tiles offset:4 bytes
             * num tiles: 2 bytes
             * num tile textures: 2 bytes
             * [id:byte. strlen: byte. string]*
             * (0)012 - texture id. 34 - rotation. 567 - up, (1)012 - right, 345-down, 67(2)0 - left
             * (2)12 - type, 34567 - reserved (3)01234567 - reserved
             */
            List<byte> data = new List<byte>();
            data.Add(Convert.ToByte('U'));
            data.Add(Convert.ToByte('U'));
            data.Add(Convert.ToByte('R'));
            data.Add(Convert.ToByte('M'));
            data.Add(0); data.Add(0); data.Add(0); data.Add(0);
            Dictionary<string, int> tilesMap = mapTiles();
            int numTiles = width * height;
            data.Add(Convert.ToByte(width));
            data.Add(Convert.ToByte(height));
            byte[] sizeBytes = BitConverter.GetBytes(Convert.ToInt16(tilesMap.Count));
            data.Add(sizeBytes[0]);
            data.Add(sizeBytes[1]);

            foreach (string texName in tilesMap.Keys) {
                int id = tilesMap[texName];
                data.Add(Convert.ToByte(id));
                data.Add(Convert.ToByte(texName.Length));
                for (int i = 0; i < texName.Length; ++i) {
                    data.Add(Convert.ToByte(texName[i]));
                }
            }
            int offset = data.Count;
            byte[] offsetBytes = BitConverter.GetBytes(offset);
            data[4] = offsetBytes[0]; data[5] = offsetBytes[1]; data[6] = offsetBytes[2]; data[7] = offsetBytes[3];
            for (int i = 0; i < width; ++i) {
                for (int j = 0; j < height; ++j) {
                    TileInfo tile = tiles[i, j];
                    byte byte1 = 0;
                    byte texID = Convert.ToByte(tilesMap[Path.GetFileName(tile.tileBox.ImageLocation)]);
                    byte1 |= (byte)(texID << 5);
                    byte upWall = getWallType(tile.up);
                    byte rightWall = getWallType(tile.right);
                    byte downWall = getWallType(tile.down);
                    byte leftWall = getWallType(tile.left);
                    byte1 |= (upWall);
                    byte byte2 = 0;
                    byte2 |= (byte)(rightWall << (byte)5);
                    byte2 |= (byte)(downWall << (byte)2);
                    byte2 |= (byte)((leftWall & 6) >> 1);
                    byte byte3 = 0;
                    byte3 |= (byte)((leftWall & 1) << 7);
                    data.Add(byte1); data.Add(byte2); data.Add(byte3); data.Add(0);
                }
            }
            FileStream stream = File.Create(saveFileDialog.FileName);
            BinaryWriter writer = new BinaryWriter(stream);
            writer.Write(data.ToArray());
            writer.Close();
            stream.Close();
        }

        private void openButton_Click(object sender, EventArgs e)
        {
            DialogResult res = openFileDialog.ShowDialog();
            if (res != DialogResult.OK) {
                return;
            }

            byte[] fileBytes = File.ReadAllBytes(openFileDialog.FileName);
            if (fileBytes[0] != Convert.ToByte('U') || fileBytes[1] != Convert.ToByte('U') || fileBytes[2] != Convert.ToByte('R') || fileBytes[3] != Convert.ToByte('M')) {
                return;
            }
            /*
             * UURM:4 bytes
             * tiles offset:4 bytes
             * width: byte
             * height: byte
             * num tile textures: 2 bytes
             * [id:byte. strlen: byte. string]*
             * (0)012 - texture id. 34 - rotation. 567 - up, (1)012 - right, 345-down, 67(2)0 - left
             * (2)12 - type, 34567 - reserved (3)01234567 - reserved
             */
            int tileOffset = fileBytes[5] << 8 | fileBytes[4];
            int width = fileBytes[8];
            int height = fileBytes[9];
            int numTextures = fileBytes[11] << 8 | fileBytes[10];
            int offset = 12;
            Dictionary<int, string> textureMap = new Dictionary<int, string>();
            for (int i = 0; i < numTextures; ++i) {
                int id = fileBytes[offset++];
                int strLen = fileBytes[offset++];
                string texName = "";
                for (int j = 0; j < strLen; ++j) {
                    texName += Convert.ToChar(fileBytes[offset++]);
                }
                textureMap[id] = texName;
            }
            widthBox.Text = width.ToString();
            heightBox.Text = height.ToString();
            tiles = null;
            resizeRoom();
            tiles = new TileInfo[width, height];
            for (int i = 0; i < width; ++i) {
                for (int j = 0; j < height; ++j) {
                    byte byte1 = fileBytes[offset++];
                    byte byte2 = fileBytes[offset++];
                    byte byte3 = fileBytes[offset++];
                    offset++; //skip reserved byte;

                    int textureID = (byte1 & 0xE0) >> 5;
                    int up = byte1 & 7;
                    int right = (byte2 & 0xE0) >> 5;
                    int down = (byte2 & 0x1C) >> 2;
                    int left = (byte2 & 1) << 2 | ((byte3 & 0xC0) >> 7);

                    TileInfo tile = new TileInfo();
                    tile.x = i;
                    tile.y = j;
                    tile.tileBox = new PictureBox();
                    tile.tileBox.Left = i * 25 + 1;
                    tile.tileBox.Top = j * 25 + 1;
                    tile.tileBox.Click += new EventHandler(roomTileClick);
                    tile.tileBox.Width = 25;
                    tile.tileBox.Height = 25;
                    tile.tileBox.ImageLocation = tilesDir + "\\" + textureMap[textureID];
                    tile.up = getWallType(up);
                    tile.right = getWallType(right);
                    tile.down = getWallType(down);
                    tile.left = getWallType(left);
                    tiles[i, j] = tile;
                }
            }
            resizeRoom();
        }

        private void clearButton_Click(object sender, EventArgs e)
        {
            tiles = null;
            resizeRoom();
        }
    }
}
