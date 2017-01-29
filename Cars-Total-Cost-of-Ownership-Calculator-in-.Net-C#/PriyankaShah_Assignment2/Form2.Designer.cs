namespace PriyankaShah_Assignment2
{
    partial class Form2
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
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle2 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle3 = new System.Windows.Forms.DataGridViewCellStyle();
            this.label1 = new System.Windows.Forms.Label();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.menuToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.sAVEToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.lOADToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aDDToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.dELETEToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.textNoOfCars = new System.Windows.Forms.TextBox();
            this.gridCarDetails = new System.Windows.Forms.DataGridView();
            this.calculate = new System.Windows.Forms.Button();
            this.textReport = new System.Windows.Forms.RichTextBox();
            this.linkLabel1 = new System.Windows.Forms.LinkLabel();
            this.CarLoan = new System.Windows.Forms.Button();
            this.Make = new System.Windows.Forms.DataGridViewComboBoxColumn();
            this.Model = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.InitialPrice = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.CityMilesPerGallon = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.HwyMilesPerGallon = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.gridCarDetails)).BeginInit();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(21, 58);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(333, 25);
            this.label1.TabIndex = 0;
            this.label1.Text = "Enter Number of Cars to compare";
            // 
            // menuStrip1
            // 
            this.menuStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(966, 31);
            this.menuStrip1.TabIndex = 6;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // menuToolStripMenuItem
            // 
            this.menuToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.sAVEToolStripMenuItem,
            this.lOADToolStripMenuItem,
            this.aDDToolStripMenuItem,
            this.dELETEToolStripMenuItem});
            this.menuToolStripMenuItem.Font = new System.Drawing.Font("Segoe UI", 10.2F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.menuToolStripMenuItem.Name = "menuToolStripMenuItem";
            this.menuToolStripMenuItem.Size = new System.Drawing.Size(47, 27);
            this.menuToolStripMenuItem.Text = "File";
            this.menuToolStripMenuItem.Click += new System.EventHandler(this.menuToolStripMenuItem_Click);
            // 
            // sAVEToolStripMenuItem
            // 
            this.sAVEToolStripMenuItem.Name = "sAVEToolStripMenuItem";
            this.sAVEToolStripMenuItem.Size = new System.Drawing.Size(135, 28);
            this.sAVEToolStripMenuItem.Text = "Save";
            this.sAVEToolStripMenuItem.Click += new System.EventHandler(this.sAVEToolStripMenuItem_Click);
            // 
            // lOADToolStripMenuItem
            // 
            this.lOADToolStripMenuItem.Name = "lOADToolStripMenuItem";
            this.lOADToolStripMenuItem.Size = new System.Drawing.Size(135, 28);
            this.lOADToolStripMenuItem.Text = "Load";
            this.lOADToolStripMenuItem.Click += new System.EventHandler(this.lOADToolStripMenuItem_Click);
            // 
            // aDDToolStripMenuItem
            // 
            this.aDDToolStripMenuItem.Name = "aDDToolStripMenuItem";
            this.aDDToolStripMenuItem.Size = new System.Drawing.Size(135, 28);
            this.aDDToolStripMenuItem.Text = "Add";
            this.aDDToolStripMenuItem.Click += new System.EventHandler(this.aDDToolStripMenuItem_Click);
            // 
            // dELETEToolStripMenuItem
            // 
            this.dELETEToolStripMenuItem.Name = "dELETEToolStripMenuItem";
            this.dELETEToolStripMenuItem.Size = new System.Drawing.Size(135, 28);
            this.dELETEToolStripMenuItem.Text = "Delete";
            this.dELETEToolStripMenuItem.Click += new System.EventHandler(this.dELETEToolStripMenuItem_Click);
            // 
            // textNoOfCars
            // 
            this.textNoOfCars.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textNoOfCars.Location = new System.Drawing.Point(408, 58);
            this.textNoOfCars.Name = "textNoOfCars";
            this.textNoOfCars.Size = new System.Drawing.Size(100, 30);
            this.textNoOfCars.TabIndex = 2;
            this.textNoOfCars.TextChanged += new System.EventHandler(this.textNoOfCars_TextChanged);
            // 
            // gridCarDetails
            // 
            this.gridCarDetails.AllowUserToAddRows = false;
            this.gridCarDetails.AllowUserToDeleteRows = false;
            this.gridCarDetails.AllowUserToOrderColumns = true;
            this.gridCarDetails.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.gridCarDetails.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.gridCarDetails.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.gridCarDetails.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.Make,
            this.Model,
            this.InitialPrice,
            this.CityMilesPerGallon,
            this.HwyMilesPerGallon});
            this.gridCarDetails.Location = new System.Drawing.Point(26, 107);
            this.gridCarDetails.MultiSelect = false;
            this.gridCarDetails.Name = "gridCarDetails";
            this.gridCarDetails.RowTemplate.Height = 24;
            this.gridCarDetails.Size = new System.Drawing.Size(903, 124);
            this.gridCarDetails.TabIndex = 3;
            this.gridCarDetails.CellClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.dataGridView1_CellContentClick);
            this.gridCarDetails.CellValidating += new System.Windows.Forms.DataGridViewCellValidatingEventHandler(this.dataGridView1_CellContentClick);
            // 
            // calculate
            // 
            this.calculate.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.calculate.Cursor = System.Windows.Forms.Cursors.Hand;
            this.calculate.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.calculate.Location = new System.Drawing.Point(256, 272);
            this.calculate.Name = "calculate";
            this.calculate.Size = new System.Drawing.Size(168, 39);
            this.calculate.TabIndex = 4;
            this.calculate.Text = "Calculate";
            this.calculate.UseVisualStyleBackColor = true;
            this.calculate.Click += new System.EventHandler(this.calculate_Click);
            // 
            // textReport
            // 
            this.textReport.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textReport.Location = new System.Drawing.Point(26, 362);
            this.textReport.Name = "textReport";
            this.textReport.ReadOnly = true;
            this.textReport.Size = new System.Drawing.Size(903, 160);
            this.textReport.TabIndex = 5;
            this.textReport.Text = "";
            this.textReport.Visible = false;
            // 
            // linkLabel1
            // 
            this.linkLabel1.AutoSize = true;
            this.linkLabel1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.linkLabel1.Location = new System.Drawing.Point(833, 561);
            this.linkLabel1.Name = "linkLabel1";
            this.linkLabel1.Size = new System.Drawing.Size(96, 25);
            this.linkLabel1.TabIndex = 19;
            this.linkLabel1.TabStop = true;
            this.linkLabel1.Text = "Previous";
            this.linkLabel1.LinkClicked += new System.Windows.Forms.LinkLabelLinkClickedEventHandler(this.linkLabel1_LinkClicked);
            // 
            // CarLoan
            // 
            this.CarLoan.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.CarLoan.Cursor = System.Windows.Forms.Cursors.Hand;
            this.CarLoan.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.CarLoan.Location = new System.Drawing.Point(473, 272);
            this.CarLoan.Name = "CarLoan";
            this.CarLoan.Size = new System.Drawing.Size(168, 39);
            this.CarLoan.TabIndex = 20;
            this.CarLoan.Text = "Car Loan";
            this.CarLoan.UseVisualStyleBackColor = true;
            this.CarLoan.Click += new System.EventHandler(this.CarLoan_Click);
            // 
            // Make
            // 
            this.Make.HeaderText = "Make";
            this.Make.Items.AddRange(new object[] {
            "Chevrolet",
            "Ford",
            "Toyota",
            "Honda"});
            this.Make.Name = "Make";
            this.Make.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            this.Make.SortMode = System.Windows.Forms.DataGridViewColumnSortMode.Automatic;
            // 
            // Model
            // 
            this.Model.HeaderText = "Model";
            this.Model.Name = "Model";
            // 
            // InitialPrice
            // 
            dataGridViewCellStyle1.Format = "N5";
            dataGridViewCellStyle1.NullValue = null;
            this.InitialPrice.DefaultCellStyle = dataGridViewCellStyle1;
            this.InitialPrice.HeaderText = "Initial Price";
            this.InitialPrice.Name = "InitialPrice";
            // 
            // CityMilesPerGallon
            // 
            dataGridViewCellStyle2.Format = "N5";
            dataGridViewCellStyle2.NullValue = null;
            this.CityMilesPerGallon.DefaultCellStyle = dataGridViewCellStyle2;
            this.CityMilesPerGallon.HeaderText = "City Miles Per Gallon";
            this.CityMilesPerGallon.Name = "CityMilesPerGallon";
            // 
            // HwyMilesPerGallon
            // 
            dataGridViewCellStyle3.Format = "N5";
            dataGridViewCellStyle3.NullValue = null;
            this.HwyMilesPerGallon.DefaultCellStyle = dataGridViewCellStyle3;
            this.HwyMilesPerGallon.HeaderText = "Highway Miles Per Gallon";
            this.HwyMilesPerGallon.Name = "HwyMilesPerGallon";
            // 
            // Form2
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(966, 627);
            this.Controls.Add(this.CarLoan);
            this.Controls.Add(this.linkLabel1);
            this.Controls.Add(this.textReport);
            this.Controls.Add(this.calculate);
            this.Controls.Add(this.gridCarDetails);
            this.Controls.Add(this.textNoOfCars);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form2";
            this.Text = "Form2";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.gridCarDetails)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem menuToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem sAVEToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem lOADToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aDDToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem dELETEToolStripMenuItem;
        private System.Windows.Forms.TextBox textNoOfCars;
        private System.Windows.Forms.DataGridView gridCarDetails;
        private System.Windows.Forms.Button calculate;
        private System.Windows.Forms.RichTextBox textReport;
        private System.Windows.Forms.LinkLabel linkLabel1;
        private System.Windows.Forms.Button CarLoan;
        private System.Windows.Forms.DataGridViewComboBoxColumn Make;
        private System.Windows.Forms.DataGridViewTextBoxColumn Model;
        private System.Windows.Forms.DataGridViewTextBoxColumn InitialPrice;
        private System.Windows.Forms.DataGridViewTextBoxColumn CityMilesPerGallon;
        private System.Windows.Forms.DataGridViewTextBoxColumn HwyMilesPerGallon;
    }
}