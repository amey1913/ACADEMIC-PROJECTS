using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace PriyankaShah_Assignment2
{
    public partial class Form1 : Form
    {
        Form2 form2 = null;
        public Form1()
        {
            InitializeComponent();
            
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label1_Click_1(object sender, EventArgs e)
        {

        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void textCityMiles_TextChanged(object sender, EventArgs e)
        {
            double num1;
            if (!(textCityMiles.Text == String.Empty) && !double.TryParse(textCityMiles.Text, out num1))
            {
               // Validating textbox to allow numeric values.
                MessageBox.Show(String.Format("Kindly Enter Valid Value."));
                return;
            }

        }

        private void textHwyMiles_TextChanged(object sender, EventArgs e)
        {
            // Validating textbox to allow numeric values.
            double num1;
            if (!(textHwyMiles.Text == String.Empty) && !double.TryParse(textHwyMiles.Text, out num1))
                MessageBox.Show(String.Format("Kindly Enter Valid Value."));
        }

        private void text16_TextChanged(object sender, EventArgs e)
        {
            // Validating textbox to allow numeric values.
            double num1;
            if (!(text16.Text == String.Empty) && !double.TryParse(text16.Text, out num1))
                MessageBox.Show(String.Format("Kindly Enter Valid Value."));
        }

        private void text17_TextChanged(object sender, EventArgs e)
        {
            // Validating textbox to allow numeric values.
            double num1;
            if (!(text17.Text == String.Empty) && !double.TryParse(text17.Text, out num1))
                MessageBox.Show(String.Format("Kindly Enter Valid Value."));
        }

        private void text18_TextChanged(object sender, EventArgs e)
        {
            // Validating textbox to allow numeric values.
            double num1;
            if (!(text18.Text == String.Empty) && !double.TryParse(text18.Text, out num1))
                MessageBox.Show(String.Format("Kindly Enter Valid Value."));
        }

        private void text19_TextChanged(object sender, EventArgs e)
        {
            // Validating textbox to allow numeric values.
            double num1;
            if (!(text19.Text == String.Empty) && !double.TryParse(text19.Text, out num1))
                MessageBox.Show(String.Format("Kindly Enter Valid Value."));
        }

        private void text20_TextChanged(object sender, EventArgs e)
        {
            // Validating textbox to allow numeric values.
            double num1;
            if (!(text20.Text == String.Empty) && !double.TryParse(text20.Text, out num1))
                MessageBox.Show(String.Format("Kindly Enter Valid Value."));
        }

        private void text21_TextChanged(object sender, EventArgs e)
        {
            // Validating textbox to allow numeric values.
            double num1;
            if (!(text21.Text == String.Empty) && !double.TryParse(text21.Text, out num1))
                MessageBox.Show(String.Format("Kindly Enter Valid Value."));
        }

        private void text22_TextChanged(object sender, EventArgs e)
        {
            // Validating textbox to allow numeric values.
            double num1;
            if (!(text22.Text == String.Empty) && !double.TryParse(text22.Text, out num1))
                MessageBox.Show(String.Format("Kindly Enter Valid Value."));
        }

        private void text23_TextChanged(object sender, EventArgs e)
        {
            // Validating textbox to allow numeric values.
            double num1;
            if (!(text23.Text == String.Empty) && !double.TryParse(text23.Text, out num1))
                MessageBox.Show(String.Format("Kindly Enter Valid Value."));
        }

        private void text24_TextChanged(object sender, EventArgs e)
        {
            // Validating textbox to allow numeric values.
            double num1;
            if (!(text24.Text == String.Empty) && !double.TryParse(text24.Text, out num1))
                MessageBox.Show(String.Format("Kindly Enter Valid Value."));
        }

        private void text25_TextChanged(object sender, EventArgs e)
        {
            // Validating textbox to allow numeric values.
            double num1;
            if (!(text25.Text == String.Empty) && !double.TryParse(text25.Text, out num1))
                MessageBox.Show(String.Format("Kindly Enter Valid Value."));
        }

        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            if (!SaveUserDetails())
                return;
            if (form2 == null)
            {
                form2 = new Form2();
                form2.FormClosed += form2_FormClosed;
            }
            form2.Show();
        }

        private bool SaveUserDetails()
        {
            //SAving user details and 10 year's average gas price.
            if (text16.Text == String.Empty ||
                text17.Text == String.Empty ||
                text18.Text == String.Empty ||
                text19.Text == String.Empty ||
                text20.Text == String.Empty ||
                text21.Text == String.Empty ||
                text22.Text == String.Empty ||
                text23.Text == String.Empty ||
                text24.Text == String.Empty ||
                text25.Text == String.Empty ||
                textCityMiles.Text == String.Empty ||
                textHwyMiles.Text == String.Empty)
            {
                MessageBox.Show(String.Format("Some fields are blank.Kindly Enter Valid Input."));
                //return(false);
            }
            else
            {
                Car.AvgGas[0] = Double.Parse(text16.Text);
                Car.AvgGas[1] = Double.Parse(text17.Text);
                Car.AvgGas[2] = Double.Parse(text18.Text);
                Car.AvgGas[3] = Double.Parse(text19.Text);
                Car.AvgGas[4] = Double.Parse(text20.Text);
                Car.AvgGas[5] = Double.Parse(text21.Text);
                Car.AvgGas[6] = Double.Parse(text22.Text);
                Car.AvgGas[7] = Double.Parse(text23.Text);
                Car.AvgGas[8] = Double.Parse(text24.Text);
                Car.AvgGas[9] = Double.Parse(text25.Text);
                try
                {
                    Car.CityMiles = Double.Parse(textCityMiles.Text);
                    Car.HwyMiles = Double.Parse(textHwyMiles.Text);
                    return (true);
                }
                catch (ArgumentOutOfRangeException ex)
                {
                    MessageBox.Show(string.Format(ex.Message + "\n SaveUserDetails Out of Range Exception"));
                    
                }

            }
            return (false);
        }
        private void saveToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //Saving information into .txt file.
            if (SaveUserDetails())
            {

                try
                {
                    if (form2 == null)
                    {
                        form2 = new Form2();
                        form2.FormClosed += form2_FormClosed;
                    }
                    //Asking for user to enter file name.
                    SaveFileDialog saveFileDialog1 = new SaveFileDialog();
                    saveFileDialog1.Filter = "Text File|*.txt";
                    saveFileDialog1.Title = "Save a Car Report";
                    saveFileDialog1.ShowDialog();

                    if (saveFileDialog1.FileName != "")
                        File.WriteAllText(saveFileDialog1.FileName, form2.GetTextToSaveInFile());
                    else
                        MessageBox.Show("Kindly Enter File Name.");
                }
                catch (NullReferenceException ex)
                {
                    MessageBox.Show(string.Format(ex.Message + "\n Null Reference Exception"));
                    return;

                }
            }
        }

        private void loadToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //loading data from the file and populating the values in screen.
            if (form2 == null)
            {
                form2 = new Form2();
                form2.FormClosed += form2_FormClosed;
            }

                form2.LoadDataOnForm(this);
            }

       public void LoadUserDataOnForm()
        {
            //loading data from the file and populating the values in screen.
            this.textCityMiles.Text = Car.CityMiles.ToString();
            this.textHwyMiles.Text = Car.HwyMiles.ToString();
            this.text16.Text = Car.AvgGas[0].ToString();
            this.text17.Text = Car.AvgGas[1].ToString();
            this.text18.Text = Car.AvgGas[2].ToString();
            this.text19.Text = Car.AvgGas[3].ToString();
            this.text20.Text = Car.AvgGas[4].ToString();
            this.text21.Text = Car.AvgGas[5].ToString();
            this.text22.Text = Car.AvgGas[6].ToString();
            this.text23.Text = Car.AvgGas[7].ToString();
            this.text24.Text = Car.AvgGas[8].ToString();
            this.text25.Text = Car.AvgGas[9].ToString();
            
        }
        void form2_FormClosed(object sender, FormClosedEventArgs e)
        {
            form2 = null;  //If form is closed make sure reference is set to null
            Show();
        }
    }
}
