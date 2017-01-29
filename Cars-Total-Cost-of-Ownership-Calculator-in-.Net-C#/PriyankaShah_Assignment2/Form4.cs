using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PriyankaShah_Assignment2
{
    public partial class Form4 : Form
    {
        private double loanAmt;
        private int noOfMonths;
        private double intRate;
        private double effectiveInt;
        private double monthlyPay;
        public double LoanAmt
        {
            get
            {
                return loanAmt;
            }
            set
            {
                if (value > 0)
                    loanAmt = value;
                else
                    throw new ArgumentOutOfRangeException("Loan Amount must be greater than 0");
            }

        }
        public int NoOfMonths
        {
            get
            {
                return noOfMonths;
            }
            set
            {
                if (value > 0)
                    noOfMonths = value;
                else
                    throw new ArgumentOutOfRangeException("Number of Months must be greater than 0");
            }

        }
        public double IntRate
        {
            get
            {
                return intRate;
            }
            set
            {
                if (value > 0)
                    intRate = value;
                else
                    throw new ArgumentOutOfRangeException("Interest Rate must be greater than 0");
            }

        }
        public double EffectiveInt
        {
            get
            {
                return effectiveInt;
            }
            set
            {
                    effectiveInt = value;
            }

        }
        public double MonthlyPay
        {
            get
            {
                return monthlyPay;
            }
            set
            {
                    monthlyPay = value;
            }

        }
        public Form4(double loanAmt, int noOfMonths, double intRate, double effectiveInt, double monthlyPay)
        {
            //fully parameterized constructor
            InitializeComponent();
            LoanAmt = loanAmt;
            NoOfMonths = noOfMonths;
            IntRate = intRate;
            EffectiveInt = effectiveInt;
            MonthlyPay = monthlyPay;
            loadLoanDetails();
        }

        private void loadLoanDetails()
        {
            //loading the amortized report of the car loan when form loads.
            for (int i = 0; i < NoOfMonths; i++)
                gridLoanDetails.Rows.Add();

            int payNo = 0;
            double totalIntAmt = 0, remainingAmt = LoanAmt, intAmt = 0, principal = 0;

            foreach (DataGridViewRow row in gridLoanDetails.Rows)
            {
                intAmt = 0;
                principal = 0;
                row.Cells[0].Value = ++payNo;
                row.Cells[1].Value = Math.Round(MonthlyPay,2).ToString();

                intAmt = Math.Round(EffectiveInt * remainingAmt, 2);
                principal = Math.Round(MonthlyPay - intAmt, 2);
                remainingAmt = Math.Round(LoanAmt - principal, 2);

                row.Cells[2].Value = principal.ToString();
                row.Cells[3].Value = intAmt.ToString();
                row.Cells[4].Value = remainingAmt.ToString();

                totalIntAmt += intAmt;
                gridLoanDetails.Refresh();
                
            }
            //Displaying summary of the car loan.
            label1.Text = Math.Round(LoanAmt, 2).ToString();
            label2.Text = Math.Round((MonthlyPay * NoOfMonths), 2).ToString();
            label3.Text = Math.Round(totalIntAmt, 2).ToString();


        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void gridCarDetails_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void groupBox1_Enter(object sender, EventArgs e)
        {

        }
    }
}
