namespace PriyankaShah_Assignment2
{
    partial class Form4
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
            this.gridLoanDetails = new System.Windows.Forms.DataGridView();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.TotalAmt = new System.Windows.Forms.Label();
            this.Initial = new System.Windows.Forms.Label();
            this.TotalInt = new System.Windows.Forms.Label();
            this.hybridCarEvaluation = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.PaymentNumber = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Amount = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Principal = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Interest = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.Balance = new System.Windows.Forms.DataGridViewTextBoxColumn();
            ((System.ComponentModel.ISupportInitialize)(this.gridLoanDetails)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // gridLoanDetails
            // 
            this.gridLoanDetails.AllowUserToAddRows = false;
            this.gridLoanDetails.AllowUserToDeleteRows = false;
            this.gridLoanDetails.AllowUserToOrderColumns = true;
            this.gridLoanDetails.AutoSizeColumnsMode = System.Windows.Forms.DataGridViewAutoSizeColumnsMode.Fill;
            this.gridLoanDetails.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.gridLoanDetails.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.gridLoanDetails.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.PaymentNumber,
            this.Amount,
            this.Principal,
            this.Interest,
            this.Balance});
            this.gridLoanDetails.Location = new System.Drawing.Point(40, 61);
            this.gridLoanDetails.MultiSelect = false;
            this.gridLoanDetails.Name = "gridLoanDetails";
            this.gridLoanDetails.RowTemplate.Height = 24;
            this.gridLoanDetails.Size = new System.Drawing.Size(902, 370);
            this.gridLoanDetails.TabIndex = 4;
            this.gridLoanDetails.CellContentClick += new System.Windows.Forms.DataGridViewCellEventHandler(this.gridCarDetails_CellContentClick);
            // 
            // groupBox1
            // 
            this.groupBox1.BackgroundImageLayout = System.Windows.Forms.ImageLayout.None;
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.TotalInt);
            this.groupBox1.Controls.Add(this.Initial);
            this.groupBox1.Controls.Add(this.TotalAmt);
            this.groupBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.8F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox1.Location = new System.Drawing.Point(535, 448);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(407, 167);
            this.groupBox1.TabIndex = 5;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Loan Summary";
            this.groupBox1.Enter += new System.EventHandler(this.groupBox1_Enter);
            // 
            // TotalAmt
            // 
            this.TotalAmt.AutoSize = true;
            this.TotalAmt.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TotalAmt.Location = new System.Drawing.Point(16, 79);
            this.TotalAmt.Name = "TotalAmt";
            this.TotalAmt.Size = new System.Drawing.Size(169, 20);
            this.TotalAmt.TabIndex = 9;
            this.TotalAmt.Text = "Total Amount Paid:";
            this.TotalAmt.Click += new System.EventHandler(this.label2_Click);
            // 
            // Initial
            // 
            this.Initial.AutoSize = true;
            this.Initial.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Initial.Location = new System.Drawing.Point(16, 37);
            this.Initial.Name = "Initial";
            this.Initial.Size = new System.Drawing.Size(177, 20);
            this.Initial.TabIndex = 10;
            this.Initial.Text = "Initial Loan Amount:";
            // 
            // TotalInt
            // 
            this.TotalInt.AutoSize = true;
            this.TotalInt.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TotalInt.Location = new System.Drawing.Point(16, 122);
            this.TotalInt.Name = "TotalInt";
            this.TotalInt.Size = new System.Drawing.Size(170, 20);
            this.TotalInt.TabIndex = 11;
            this.TotalInt.Text = "Total Interest Paid:";
            // 
            // hybridCarEvaluation
            // 
            this.hybridCarEvaluation.AutoSize = true;
            this.hybridCarEvaluation.Font = new System.Drawing.Font("Microsoft Sans Serif", 19.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.hybridCarEvaluation.Location = new System.Drawing.Point(346, 9);
            this.hybridCarEvaluation.Name = "hybridCarEvaluation";
            this.hybridCarEvaluation.Size = new System.Drawing.Size(297, 39);
            this.hybridCarEvaluation.TabIndex = 12;
            this.hybridCarEvaluation.Text = "Amortized Report";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(205, 37);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(0, 20);
            this.label1.TabIndex = 12;
            this.label1.Click += new System.EventHandler(this.label1_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(205, 79);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(0, 20);
            this.label2.TabIndex = 13;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(205, 122);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(0, 20);
            this.label3.TabIndex = 14;
            // 
            // PaymentNumber
            // 
            this.PaymentNumber.HeaderText = "Payment Number";
            this.PaymentNumber.Name = "PaymentNumber";
            this.PaymentNumber.ReadOnly = true;
            this.PaymentNumber.Resizable = System.Windows.Forms.DataGridViewTriState.True;
            // 
            // Amount
            // 
            this.Amount.HeaderText = "Amount";
            this.Amount.Name = "Amount";
            this.Amount.ReadOnly = true;
            // 
            // Principal
            // 
            dataGridViewCellStyle1.Format = "N5";
            dataGridViewCellStyle1.NullValue = null;
            this.Principal.DefaultCellStyle = dataGridViewCellStyle1;
            this.Principal.HeaderText = "Principal";
            this.Principal.Name = "Principal";
            this.Principal.ReadOnly = true;
            // 
            // Interest
            // 
            dataGridViewCellStyle2.Format = "N5";
            dataGridViewCellStyle2.NullValue = null;
            this.Interest.DefaultCellStyle = dataGridViewCellStyle2;
            this.Interest.HeaderText = "Interest";
            this.Interest.Name = "Interest";
            this.Interest.ReadOnly = true;
            // 
            // Balance
            // 
            dataGridViewCellStyle3.Format = "N5";
            dataGridViewCellStyle3.NullValue = null;
            this.Balance.DefaultCellStyle = dataGridViewCellStyle3;
            this.Balance.HeaderText = "Balance";
            this.Balance.Name = "Balance";
            this.Balance.ReadOnly = true;
            // 
            // Form4
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(978, 627);
            this.Controls.Add(this.hybridCarEvaluation);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.gridLoanDetails);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Name = "Form4";
            this.Text = "Form4";
            ((System.ComponentModel.ISupportInitialize)(this.gridLoanDetails)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView gridLoanDetails;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label TotalInt;
        private System.Windows.Forms.Label Initial;
        private System.Windows.Forms.Label TotalAmt;
        private System.Windows.Forms.Label hybridCarEvaluation;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.DataGridViewTextBoxColumn PaymentNumber;
        private System.Windows.Forms.DataGridViewTextBoxColumn Amount;
        private System.Windows.Forms.DataGridViewTextBoxColumn Principal;
        private System.Windows.Forms.DataGridViewTextBoxColumn Interest;
        private System.Windows.Forms.DataGridViewTextBoxColumn Balance;
    }
}