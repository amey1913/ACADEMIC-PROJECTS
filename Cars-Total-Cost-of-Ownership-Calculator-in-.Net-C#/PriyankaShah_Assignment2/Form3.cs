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
    public partial class Form3 : Form
    {
        DataGridViewSelectedRowCollection selectedRow;
        public Form3(DataGridViewSelectedRowCollection selectedRow)
        {
            //fully parameterized constructor
            InitializeComponent();
            this.selectedRow = selectedRow;
          
        }
        
        private void textLoanPeriod_TextChanged(object sender, EventArgs e)
        {
            // Validating textbox to allow numeric values.
            int num1;
            if (!(textLoanPeriod.Text == String.Empty) && !int.TryParse(textLoanPeriod.Text, out num1))
            {
                MessageBox.Show(String.Format("Kindly Enter Valid Value."));
                return;
            }

        }

        private void textDownPay_TextChanged(object sender, EventArgs e)
        {
            // Validating textbox to allow numeric values.
            double num1;
            if (!(textDwnPay.Text == String.Empty) && !double.TryParse(textDwnPay.Text, out num1))
            {
                MessageBox.Show(String.Format("Kindly Enter Valid Value."));
                return;
            }

        }

        private void textAnnualInt_TextChanged(object sender, EventArgs e)
        {
            // Validating textbox to allow numeric values.
            double num1;
            if (!(textAnnualInt.Text == String.Empty) && !double.TryParse(textAnnualInt.Text, out num1))
            {
                MessageBox.Show(String.Format("Kindly Enter Valid Value."));
                return;
            }

        }

        private void amortized_Click(object sender, EventArgs e)
        {
            // Calculating the amortized report of the selected car based on intial price of the car, the specified loan period and interest rate.
            try
            {
                double principalAmt = double.Parse(selectedRow[0].Cells["InitialPrice"].Value.ToString()) - double.Parse(textDwnPay.Text);
                int noOfMonths = int.Parse(textLoanPeriod.Text) * 12;
                double intRate = double.Parse(textAnnualInt.Text);
                double effectiveInt = Math.Round((intRate / 100) / 12, 2);
                double monthlyPay = principalAmt * (effectiveInt / (1 - Math.Pow(1 + effectiveInt, -noOfMonths)));

                //opening form to show the amortized report of the car loan
                Form4 form4 = new Form4(principalAmt, noOfMonths, intRate, effectiveInt, monthlyPay);
                form4.Show();
            }
            catch (ArgumentOutOfRangeException ex)
            {
                MessageBox.Show(string.Format(ex.Message + "\nOut of Range Exception"));
                return;
            }
            catch (FormatException ex1)
            {
                MessageBox.Show(string.Format(ex1.Message + "\nFormat Exception"));
                return;
            }

        }
    }
}
