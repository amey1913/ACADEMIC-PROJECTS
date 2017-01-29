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
    public partial class Form2 : Form    {
        List<Car> car = new List<Car>();
        Form1 form1 = null;
        
        public Form2()
        {
            InitializeComponent();
        }

        private void textNoOfCars_TextChanged(object sender, EventArgs e)
        {
            // Validating textbox to allow numeric values.

            int num1;
            if (!(textNoOfCars.Text == String.Empty) && !int.TryParse(textNoOfCars.Text, out num1))
                MessageBox.Show(String.Format("Kindly Enter Valid Value."));
            else
            {
                if (!(textNoOfCars.Text == String.Empty))
                {
                    for (int i = 0; i < int.Parse(textNoOfCars.Text); i++)
                        this.gridCarDetails.Rows.Add();
                }
            }

        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellEventArgs e)
        {
            textNoOfCars.Enabled = false;

        }

        private void calculate_Click(object sender, EventArgs e)
        {
            //On click, displaying all data in the report along with calculated Total cost of Gasoline and total Cost of Ownership.
            car.Clear();
            foreach (DataGridViewRow row in gridCarDetails.Rows)
            {
                try
                {
                    if ((row.Cells["Make"].Value.ToString() != String.Empty) &&
                        (row.Cells["Model"].Value.ToString() != String.Empty) &&
                        (row.Cells["InitialPrice"].Value.ToString() != String.Empty) &&
                        (row.Cells["CityMilesPerGallon"].Value.ToString() != String.Empty) &&
                        (row.Cells["HwyMilesPerGallon"].Value.ToString() != String.Empty))
                    {
                        try
                        {
                            //Adding values in list of car.
                            car.Add(new Car(row.Cells["Make"].Value.ToString(),
                                            row.Cells["Model"].Value.ToString(),
                                            double.Parse(row.Cells["InitialPrice"].Value.ToString()),
                                            double.Parse(row.Cells["CityMilesPerGallon"].Value.ToString()),
                                            double.Parse(row.Cells["HwyMilesPerGallon"].Value.ToString())));
                            textReport.Visible = true;


                        }
                        catch (ArgumentOutOfRangeException ex)
                        {
                            MessageBox.Show(String.Format(ex.Message + "\n Out of Range."));
                            return;
                        }
                    }
                }
                catch (NullReferenceException ex)
                {
                    MessageBox.Show(String.Format(ex.Message + "\n Null Reference."));
                    return;
                }
            }
            DisplayReport();
        }

        private void DisplayReport()
        {
            //This method will print report in multiline textfield.
            textReport.Text = "Miles Driven:\nCity Miles: " + Car.CityMiles + "\nHighway Miles: " + Car.HwyMiles +
                                "\nCost of Average Gas of each year:\n";
            int count = 1;
            foreach (double d in Car.AvgGas)
            {
                textReport.Text += "Year " + count + ": " + d + "\n";
                count++;
            }
            textReport.Text += "\n\nMake/Model\tMPG Rating City/Hwy\tInitial Cost\tTotal Cost of Gas\tTotal Cost of Ownership\n";
            foreach (Car c in car)
                textReport.Text += c.ToString();
            
        }

        private void dataGridView1_CellContentClick(object sender, DataGridViewCellValidatingEventArgs e)
        {
            //Validating Columns Initial Price, City Miles per Gallon and Highway Miles per Gallon value
            if (e.ColumnIndex == 2 || e.ColumnIndex == 3 || e.ColumnIndex == 4)
            {
                double i;
                if (!(Convert.ToString(e.FormattedValue) == String.Empty) && !double.TryParse(Convert.ToString(e.FormattedValue), out i))
                {
                    e.Cancel = true;
                    MessageBox.Show("Kindly Enter Valid Value.");
                }
            }
        }

        private void sAVEToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //Saving Report into Text File.
            SaveFileDialog saveFileDialog1 = new SaveFileDialog();
            saveFileDialog1.Filter = "Text File|*.txt";
            saveFileDialog1.Title = "Save a Car Report";
            saveFileDialog1.ShowDialog();
            
            if (saveFileDialog1.FileName != "")
               File.WriteAllText(saveFileDialog1.FileName, GetTextToSaveInFile());
            else
                MessageBox.Show("Kindly Enter File Name.");
        }

        public string GetTextToSaveInFile()
        {
            //Formatting the text to save into file.
            string reportText;
            reportText = car.Count + "|" + Car.CityMiles.ToString() + "|" + Car.HwyMiles.ToString() + "|";

            foreach (double d in Car.AvgGas)
                reportText += d.ToString() + "|";

            foreach (Car c in car)
            {
                reportText += c.Make + "|" + c.Model + "|" + c.InitialPrice.ToString() + "|"
                            + c.Cpg.ToString() + "|" + c.Hpg.ToString() + "|";
            }

            return (reportText);
        }
        private void menuToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }

        private void lOADToolStripMenuItem_Click(object sender, EventArgs e)
        {
            LoadDataOnForm(form1);
        }

        public void LoadDataOnForm(Form1 form)
        {
            //loading data from the file and populating the values in screen.
            String readText = "";
            form1 = form;
            OpenFileDialog openFileDialog1 = new OpenFileDialog();
            if (openFileDialog1.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                textReport.Visible = true;

                string ext = Path.GetExtension(openFileDialog1.FileName);

                if (ext.Equals(".txt"))
                {
                    try
                    {
                        System.IO.StreamReader sr = new System.IO.StreamReader(openFileDialog1.FileName);
                        readText = sr.ReadToEnd();
                        sr.Close();
                    }
                    catch (IOException ex)
                    {
                        MessageBox.Show(String.Format(ex.Message + "\n Error in File Operation."));
                        return;
                    }

                }
                else
                    MessageBox.Show("Enter Valid .txt File");
            }
            try
            {
                string[] loadText = readText.Split('|');
                car.Clear();
                int num = gridCarDetails.RowCount;
                
                for (int i = 0; i < num; i++)
                    gridCarDetails.Rows.RemoveAt(0);

                int count = 1;
                
                
                try
                {
                    Car.CityMiles = Convert.ToDouble(loadText[count++]);
                    Car.HwyMiles = Convert.ToDouble(loadText[count++]);
                    for (int i = 0; i < 10; i++)
                    {
                        Car.AvgGas[i] = Convert.ToDouble(loadText[count++]);
                    }
                }
                catch (ArgumentOutOfRangeException ex)
                {
                    MessageBox.Show(string.Format(ex.Message + "\n LoadDataOnForm Out of Range Exception"));
                    return;
                }
                catch (Exception ex)
                {
                    MessageBox.Show(string.Format(ex.Message + "\n LoadDataOnForm Exception"));
                    return;
                }
                for (int i = 0; i < Convert.ToInt32(loadText[0]); i++)
                {
                    car.Add(new Car(loadText[count++],
                                    loadText[count++],
                                    double.Parse(loadText[count++]),
                                    double.Parse(loadText[count++]),
                                    double.Parse(loadText[count++])));
                    this.gridCarDetails.Rows.Add();
                    gridCarDetails.Rows[i].Cells["Make"].Value = car[i].Make;
                    gridCarDetails.Rows[i].Cells["Model"].Value = car[i].Model;
                    gridCarDetails.Rows[i].Cells["InitialPrice"].Value = car[i].InitialPrice.ToString();
                    gridCarDetails.Rows[i].Cells["CityMilesPerGallon"].Value = car[i].Cpg.ToString();
                    gridCarDetails.Rows[i].Cells["HwyMilesPerGallon"].Value = car[i].Hpg.ToString();

                }
                label1.Visible = false;
                textNoOfCars.Visible = false;
                if (form1 == null)
                {
                    form1 = new Form1();
                    form1.FormClosed += form1_FormClosed;
                }
                form1.LoadUserDataOnForm();
                
                DisplayReport();
            }
            catch (FormatException ex)
            {
                MessageBox.Show(string.Format(ex.Message + "\n Error in Data present in File"));
                return;
            }


        }
        void form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            form1 = null;  //If form is closed, reference is set to null
            Show();
        }

        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            //go to previous form.
            Hide();
        }

        private void dELETEToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //Selected row from the grid view will be deleted when this menu item is selected.
            foreach (DataGridViewRow r in gridCarDetails.Rows)
            {
                if (r.Selected == true)
                {
                        car.RemoveAt(r.Index);
                        gridCarDetails.Rows.RemoveAt(r.Index);
                        gridCarDetails.Refresh();
                }
            }
        }

        private void aDDToolStripMenuItem_Click(object sender, EventArgs e)
        {
            //row will be added to the grid view when this menu item is selected.
            this.gridCarDetails.Rows.Add();
        }

        private void CarLoan_Click(object sender, EventArgs e)
        {
            // Opening form3 to accept details of car loan for the selected car.
            foreach (DataGridViewRow r in gridCarDetails.Rows)
            {
                if (r.Selected == true)
                {
                    DataGridViewSelectedRowCollection selectedRow = gridCarDetails.SelectedRows;
                    Form3 form3 = new Form3(selectedRow);
                    form3.Show();
                }
            }
        }
    }
}
