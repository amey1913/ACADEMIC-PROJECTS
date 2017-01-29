namespace PriyankaShah_Assignment2
{
    partial class Form3
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
            this.textAnnualInt = new System.Windows.Forms.TextBox();
            this.textDwnPay = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.hybridCarEvaluation = new System.Windows.Forms.Label();
            this.textLoanPeriod = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.amortized = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // textAnnualInt
            // 
            this.textAnnualInt.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textAnnualInt.Location = new System.Drawing.Point(411, 173);
            this.textAnnualInt.Name = "textAnnualInt";
            this.textAnnualInt.Size = new System.Drawing.Size(124, 30);
            this.textAnnualInt.TabIndex = 11;
            this.textAnnualInt.TextChanged += new System.EventHandler(this.textAnnualInt_TextChanged);
            // 
            // textDwnPay
            // 
            this.textDwnPay.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textDwnPay.Location = new System.Drawing.Point(411, 124);
            this.textDwnPay.Name = "textDwnPay";
            this.textDwnPay.Size = new System.Drawing.Size(124, 30);
            this.textDwnPay.TabIndex = 10;
            this.textDwnPay.TextChanged += new System.EventHandler(this.textDownPay_TextChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(74, 180);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(232, 20);
            this.label3.TabIndex = 9;
            this.label3.Text = "Enter Annual Interest Rate";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(74, 131);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(260, 20);
            this.label2.TabIndex = 8;
            this.label2.Text = "Enter  Down Payment Amount";
            // 
            // hybridCarEvaluation
            // 
            this.hybridCarEvaluation.AutoSize = true;
            this.hybridCarEvaluation.Font = new System.Drawing.Font("Microsoft Sans Serif", 19.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.hybridCarEvaluation.Location = new System.Drawing.Point(166, 42);
            this.hybridCarEvaluation.Name = "hybridCarEvaluation";
            this.hybridCarEvaluation.Size = new System.Drawing.Size(276, 38);
            this.hybridCarEvaluation.TabIndex = 6;
            this.hybridCarEvaluation.Text = "Car Loan Details";
            // 
            // textLoanPeriod
            // 
            this.textLoanPeriod.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textLoanPeriod.Location = new System.Drawing.Point(411, 222);
            this.textLoanPeriod.Name = "textLoanPeriod";
            this.textLoanPeriod.Size = new System.Drawing.Size(124, 30);
            this.textLoanPeriod.TabIndex = 13;
            this.textLoanPeriod.TextChanged += new System.EventHandler(this.textLoanPeriod_TextChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.2F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(74, 229);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(161, 20);
            this.label1.TabIndex = 12;
            this.label1.Text = "Enter Loan Period";
            // 
            // amortized
            // 
            this.amortized.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Center;
            this.amortized.Cursor = System.Windows.Forms.Cursors.Hand;
            this.amortized.Font = new System.Drawing.Font("Microsoft Sans Serif", 13.8F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.amortized.Location = new System.Drawing.Point(173, 301);
            this.amortized.Name = "amortized";
            this.amortized.Size = new System.Drawing.Size(286, 79);
            this.amortized.TabIndex = 14;
            this.amortized.Text = "Generate Amortized Report";
            this.amortized.UseVisualStyleBackColor = true;
            this.amortized.Click += new System.EventHandler(this.amortized_Click);
            // 
            // Form3
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(596, 446);
            this.Controls.Add(this.amortized);
            this.Controls.Add(this.textLoanPeriod);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.textAnnualInt);
            this.Controls.Add(this.textDwnPay);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.hybridCarEvaluation);
            this.Name = "Form3";
            this.Text = "Form3";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox textAnnualInt;
        private System.Windows.Forms.TextBox textDwnPay;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label hybridCarEvaluation;
        private System.Windows.Forms.TextBox textLoanPeriod;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button amortized;
    }
}