namespace UUEditor
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.nameLabel = new System.Windows.Forms.Label();
            this.nameBox = new System.Windows.Forms.TextBox();
            this.widthLabel = new System.Windows.Forms.Label();
            this.widthBox = new System.Windows.Forms.TextBox();
            this.heightBox = new System.Windows.Forms.TextBox();
            this.heightLabel = new System.Windows.Forms.Label();
            this.tilesPanel = new System.Windows.Forms.Panel();
            this.tilesDirLabel = new System.Windows.Forms.Label();
            this.reloadTilesButton = new System.Windows.Forms.Button();
            this.setTilesDirButton = new System.Windows.Forms.Button();
            this.selectTilesDirDialog = new System.Windows.Forms.FolderBrowserDialog();
            this.roomTilesPanel = new System.Windows.Forms.Panel();
            this.resizeButton = new System.Windows.Forms.Button();
            this.panel2 = new System.Windows.Forms.Panel();
            this.downPanel = new System.Windows.Forms.Panel();
            this.rightPanel = new System.Windows.Forms.Panel();
            this.leftPanel = new System.Windows.Forms.Panel();
            this.upPanel = new System.Windows.Forms.Panel();
            this.currentTileBox = new System.Windows.Forms.PictureBox();
            this.yBox = new System.Windows.Forms.TextBox();
            this.yLabel = new System.Windows.Forms.Label();
            this.xBox = new System.Windows.Forms.TextBox();
            this.xLabel = new System.Windows.Forms.Label();
            this.saveButton = new System.Windows.Forms.Button();
            this.saveFileDialog = new System.Windows.Forms.SaveFileDialog();
            this.openButton = new System.Windows.Forms.Button();
            this.openFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.clearButton = new System.Windows.Forms.Button();
            this.tilesPanel.SuspendLayout();
            this.panel2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.currentTileBox)).BeginInit();
            this.SuspendLayout();
            // 
            // nameLabel
            // 
            this.nameLabel.AutoSize = true;
            this.nameLabel.Location = new System.Drawing.Point(12, 9);
            this.nameLabel.Name = "nameLabel";
            this.nameLabel.Size = new System.Drawing.Size(35, 13);
            this.nameLabel.TabIndex = 0;
            this.nameLabel.Text = "Name";
            // 
            // nameBox
            // 
            this.nameBox.Location = new System.Drawing.Point(12, 25);
            this.nameBox.Name = "nameBox";
            this.nameBox.Size = new System.Drawing.Size(100, 20);
            this.nameBox.TabIndex = 1;
            this.nameBox.Text = "New room";
            // 
            // widthLabel
            // 
            this.widthLabel.AutoSize = true;
            this.widthLabel.Location = new System.Drawing.Point(118, 9);
            this.widthLabel.Name = "widthLabel";
            this.widthLabel.Size = new System.Drawing.Size(35, 13);
            this.widthLabel.TabIndex = 2;
            this.widthLabel.Text = "Width";
            // 
            // widthBox
            // 
            this.widthBox.Location = new System.Drawing.Point(121, 25);
            this.widthBox.Name = "widthBox";
            this.widthBox.Size = new System.Drawing.Size(41, 20);
            this.widthBox.TabIndex = 3;
            this.widthBox.Text = "2";
            // 
            // heightBox
            // 
            this.heightBox.Location = new System.Drawing.Point(168, 25);
            this.heightBox.Name = "heightBox";
            this.heightBox.Size = new System.Drawing.Size(41, 20);
            this.heightBox.TabIndex = 5;
            this.heightBox.Text = "2";
            // 
            // heightLabel
            // 
            this.heightLabel.AutoSize = true;
            this.heightLabel.Location = new System.Drawing.Point(165, 9);
            this.heightLabel.Name = "heightLabel";
            this.heightLabel.Size = new System.Drawing.Size(38, 13);
            this.heightLabel.TabIndex = 4;
            this.heightLabel.Text = "Height";
            // 
            // tilesPanel
            // 
            this.tilesPanel.AccessibleName = "";
            this.tilesPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.tilesPanel.Controls.Add(this.tilesDirLabel);
            this.tilesPanel.Controls.Add(this.reloadTilesButton);
            this.tilesPanel.Controls.Add(this.setTilesDirButton);
            this.tilesPanel.Location = new System.Drawing.Point(805, 9);
            this.tilesPanel.Name = "tilesPanel";
            this.tilesPanel.Size = new System.Drawing.Size(234, 580);
            this.tilesPanel.TabIndex = 6;
            // 
            // tilesDirLabel
            // 
            this.tilesDirLabel.AutoSize = true;
            this.tilesDirLabel.Location = new System.Drawing.Point(3, 0);
            this.tilesDirLabel.Name = "tilesDirLabel";
            this.tilesDirLabel.Size = new System.Drawing.Size(93, 13);
            this.tilesDirLabel.TabIndex = 2;
            this.tilesDirLabel.Text = "No folder selected";
            // 
            // reloadTilesButton
            // 
            this.reloadTilesButton.Location = new System.Drawing.Point(154, 552);
            this.reloadTilesButton.Name = "reloadTilesButton";
            this.reloadTilesButton.Size = new System.Drawing.Size(75, 23);
            this.reloadTilesButton.TabIndex = 1;
            this.reloadTilesButton.Text = "Reload tiles";
            this.reloadTilesButton.UseVisualStyleBackColor = true;
            this.reloadTilesButton.Click += new System.EventHandler(this.reloadTilesButton_Click);
            // 
            // setTilesDirButton
            // 
            this.setTilesDirButton.Location = new System.Drawing.Point(3, 552);
            this.setTilesDirButton.Name = "setTilesDirButton";
            this.setTilesDirButton.Size = new System.Drawing.Size(84, 23);
            this.setTilesDirButton.TabIndex = 0;
            this.setTilesDirButton.Text = "Set tiles folder";
            this.setTilesDirButton.UseVisualStyleBackColor = true;
            this.setTilesDirButton.Click += new System.EventHandler(this.setTilesDirButton_Click);
            // 
            // roomTilesPanel
            // 
            this.roomTilesPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.roomTilesPanel.Location = new System.Drawing.Point(15, 51);
            this.roomTilesPanel.Name = "roomTilesPanel";
            this.roomTilesPanel.Size = new System.Drawing.Size(65, 65);
            this.roomTilesPanel.TabIndex = 7;
            // 
            // resizeButton
            // 
            this.resizeButton.Location = new System.Drawing.Point(489, 9);
            this.resizeButton.Name = "resizeButton";
            this.resizeButton.Size = new System.Drawing.Size(75, 23);
            this.resizeButton.TabIndex = 8;
            this.resizeButton.Text = "Resize";
            this.resizeButton.UseVisualStyleBackColor = true;
            this.resizeButton.Click += new System.EventHandler(this.resizeButton_Click);
            // 
            // panel2
            // 
            this.panel2.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel2.Controls.Add(this.downPanel);
            this.panel2.Controls.Add(this.rightPanel);
            this.panel2.Controls.Add(this.leftPanel);
            this.panel2.Controls.Add(this.upPanel);
            this.panel2.Controls.Add(this.currentTileBox);
            this.panel2.Controls.Add(this.yBox);
            this.panel2.Controls.Add(this.yLabel);
            this.panel2.Controls.Add(this.xBox);
            this.panel2.Controls.Add(this.xLabel);
            this.panel2.Location = new System.Drawing.Point(570, 9);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(229, 580);
            this.panel2.TabIndex = 9;
            // 
            // downPanel
            // 
            this.downPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.downPanel.Location = new System.Drawing.Point(75, 227);
            this.downPanel.Name = "downPanel";
            this.downPanel.Size = new System.Drawing.Size(76, 80);
            this.downPanel.TabIndex = 6;
            // 
            // rightPanel
            // 
            this.rightPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.rightPanel.Location = new System.Drawing.Point(144, 141);
            this.rightPanel.Name = "rightPanel";
            this.rightPanel.Size = new System.Drawing.Size(76, 80);
            this.rightPanel.TabIndex = 6;
            // 
            // leftPanel
            // 
            this.leftPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.leftPanel.Location = new System.Drawing.Point(6, 141);
            this.leftPanel.Name = "leftPanel";
            this.leftPanel.Size = new System.Drawing.Size(76, 80);
            this.leftPanel.TabIndex = 6;
            // 
            // upPanel
            // 
            this.upPanel.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.upPanel.Location = new System.Drawing.Point(75, 55);
            this.upPanel.Name = "upPanel";
            this.upPanel.Size = new System.Drawing.Size(76, 80);
            this.upPanel.TabIndex = 5;
            // 
            // currentTileBox
            // 
            this.currentTileBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.currentTileBox.Location = new System.Drawing.Point(88, 157);
            this.currentTileBox.Name = "currentTileBox";
            this.currentTileBox.Size = new System.Drawing.Size(50, 50);
            this.currentTileBox.TabIndex = 4;
            this.currentTileBox.TabStop = false;
            // 
            // yBox
            // 
            this.yBox.Enabled = false;
            this.yBox.Location = new System.Drawing.Point(26, 29);
            this.yBox.Name = "yBox";
            this.yBox.Size = new System.Drawing.Size(100, 20);
            this.yBox.TabIndex = 3;
            // 
            // yLabel
            // 
            this.yLabel.AutoSize = true;
            this.yLabel.Location = new System.Drawing.Point(3, 32);
            this.yLabel.Name = "yLabel";
            this.yLabel.Size = new System.Drawing.Size(17, 13);
            this.yLabel.TabIndex = 2;
            this.yLabel.Text = "Y:";
            // 
            // xBox
            // 
            this.xBox.Enabled = false;
            this.xBox.Location = new System.Drawing.Point(26, 3);
            this.xBox.Name = "xBox";
            this.xBox.Size = new System.Drawing.Size(100, 20);
            this.xBox.TabIndex = 1;
            // 
            // xLabel
            // 
            this.xLabel.AutoSize = true;
            this.xLabel.Location = new System.Drawing.Point(3, 6);
            this.xLabel.Name = "xLabel";
            this.xLabel.Size = new System.Drawing.Size(17, 13);
            this.xLabel.TabIndex = 0;
            this.xLabel.Text = "X:";
            // 
            // saveButton
            // 
            this.saveButton.Location = new System.Drawing.Point(489, 66);
            this.saveButton.Name = "saveButton";
            this.saveButton.Size = new System.Drawing.Size(75, 23);
            this.saveButton.TabIndex = 10;
            this.saveButton.Text = "Save";
            this.saveButton.UseVisualStyleBackColor = true;
            this.saveButton.Click += new System.EventHandler(this.saveButton_Click);
            // 
            // saveFileDialog
            // 
            this.saveFileDialog.Filter = "RRM files|*.rrm";
            // 
            // openButton
            // 
            this.openButton.Location = new System.Drawing.Point(489, 95);
            this.openButton.Name = "openButton";
            this.openButton.Size = new System.Drawing.Size(75, 23);
            this.openButton.TabIndex = 11;
            this.openButton.Text = "Open";
            this.openButton.UseVisualStyleBackColor = true;
            this.openButton.Click += new System.EventHandler(this.openButton_Click);
            // 
            // openFileDialog
            // 
            this.openFileDialog.Filter = "RRM files|*.rrm";
            // 
            // clearButton
            // 
            this.clearButton.Location = new System.Drawing.Point(489, 37);
            this.clearButton.Name = "clearButton";
            this.clearButton.Size = new System.Drawing.Size(75, 23);
            this.clearButton.TabIndex = 12;
            this.clearButton.Text = "Clear";
            this.clearButton.UseVisualStyleBackColor = true;
            this.clearButton.Click += new System.EventHandler(this.clearButton_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1051, 601);
            this.Controls.Add(this.clearButton);
            this.Controls.Add(this.openButton);
            this.Controls.Add(this.saveButton);
            this.Controls.Add(this.panel2);
            this.Controls.Add(this.resizeButton);
            this.Controls.Add(this.roomTilesPanel);
            this.Controls.Add(this.tilesPanel);
            this.Controls.Add(this.heightBox);
            this.Controls.Add(this.heightLabel);
            this.Controls.Add(this.widthBox);
            this.Controls.Add(this.widthLabel);
            this.Controls.Add(this.nameBox);
            this.Controls.Add(this.nameLabel);
            this.Name = "Form1";
            this.Text = "Room editor";
            this.Load += new System.EventHandler(this.Form1_Load);
            this.tilesPanel.ResumeLayout(false);
            this.tilesPanel.PerformLayout();
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.currentTileBox)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label nameLabel;
        private System.Windows.Forms.TextBox nameBox;
        private System.Windows.Forms.Label widthLabel;
        private System.Windows.Forms.TextBox widthBox;
        private System.Windows.Forms.TextBox heightBox;
        private System.Windows.Forms.Label heightLabel;
        private System.Windows.Forms.Panel tilesPanel;
        private System.Windows.Forms.Label tilesDirLabel;
        private System.Windows.Forms.Button reloadTilesButton;
        private System.Windows.Forms.Button setTilesDirButton;
        private System.Windows.Forms.FolderBrowserDialog selectTilesDirDialog;
        private System.Windows.Forms.Panel roomTilesPanel;
        private System.Windows.Forms.Button resizeButton;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.TextBox yBox;
        private System.Windows.Forms.Label yLabel;
        private System.Windows.Forms.TextBox xBox;
        private System.Windows.Forms.Label xLabel;
        private System.Windows.Forms.PictureBox currentTileBox;
        private System.Windows.Forms.Panel downPanel;
        private System.Windows.Forms.Panel rightPanel;
        private System.Windows.Forms.Panel leftPanel;
        private System.Windows.Forms.Panel upPanel;
        private System.Windows.Forms.Button saveButton;
        private System.Windows.Forms.SaveFileDialog saveFileDialog;
        private System.Windows.Forms.Button openButton;
        private System.Windows.Forms.OpenFileDialog openFileDialog;
        private System.Windows.Forms.Button clearButton;
    }
}

