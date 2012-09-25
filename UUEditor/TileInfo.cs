using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace UUEditor
{
    public class TileInfo
    {
        public PictureBox tileBox { get; set; }
        public int x { get; set; }
        public int y { get; set; }
        public int rotation { get; set; }

        public enum WallType { Door, BlastDoor, Wall, Empty };
        public WallType up;
        public WallType right;
        public WallType down;
        public WallType left;

        public bool exists = true;
        public bool passible = true;
    }
}
