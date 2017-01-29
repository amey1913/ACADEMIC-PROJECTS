using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace PriyankaShah_Assignment2
{
    class Car
    {
        // Car class will store all details of user and car information and calculates the total cost of ownership for each car.
        private static double cityMiles;
        private static double hwyMiles;
        private static double[] avgGas = new double[10];
        public string Make { get; set; }
        public string Model { get; set; }
        private double intialPrice;
        private double cpg;
        private double hpg;

        public static double CityMiles
        {
            get
            {
                return cityMiles;
            }
            set
            {
                if (value > 0)
                    cityMiles = value;
                else
                    throw new ArgumentOutOfRangeException("city Miles must be greater than 0");
            }

        }
        public static double HwyMiles
        {
            get
            {
                return hwyMiles;
            }
            set
            {
                if (value > 0)
                    hwyMiles = value;
                else
                    throw new ArgumentOutOfRangeException("Highway miles must be greater than 0");
            }

        }
        public static double[] AvgGas 
        {
            get
            {
                return avgGas;
            }
            set
            {
                avgGas = value;
            }

        }
        public double InitialPrice
        {
            get
            {
                return intialPrice;
            }
            set
            {
                if(value > 0)
                    intialPrice = value;
                else
                    throw new ArgumentOutOfRangeException("Intial Price must be greater than 0");
            }

        }
        public double Cpg
        {
            get
            {
                return cpg;
            }
            set
            {
                if (value > 0)
                    cpg = value;
                else
                    throw new ArgumentOutOfRangeException("City Miles per Gallon must be greater than 0");
            }

        }
        public double Hpg
        {
            get
            {
                return hpg;
            }
            set
            {
                if (value > 0)
                    hpg = value;
                else
                    throw new ArgumentOutOfRangeException("Highway Miles per Gallon must be greater than 0");
            }

        }
        public Car(string make, string model, double initialPrice, double cpg, double hpg)
        {
            //Fully parameterized constructor
            this.Make = make;
            this.Model = model;
            this.InitialPrice = initialPrice;
            this.Cpg = cpg;
            this.Hpg = hpg;
        }

        public void CalculateCostOfOwnership(out double totalGas, out double totalCostOfOwn)
        {
            //Calculates the total cost of gasoline and total cost of ownership for each car.
            double tempCity = CityMiles / Cpg;
            double tempHwy = HwyMiles / Hpg;
            double totalCityGas = 0;
            double totalHwyGas = 0;
            for (int i = 0; i < 10; i++)
            {
                totalCityGas += (AvgGas[i] + tempCity);
                totalHwyGas += (AvgGas[i] + tempHwy);
            }
            totalGas = totalCityGas + totalHwyGas;
            totalCostOfOwn = InitialPrice + totalGas;
        }
        public override string ToString()
        {
            double totalGas = 0;
            double totalCostOfOwn = 0;

            CalculateCostOfOwnership(out totalGas, out totalCostOfOwn);
            return (String.Format("{0}/{1}\t\t{2}/{3}\t\t\t{4}\t\t\t{5}\t\t\t{6}\n",Make ,Model, 
                                                    Math.Round(Cpg,2), 
                                                    Math.Round(Hpg,2), 
                                                    Math.Round(InitialPrice,2), 
                                                    Math.Round(totalGas,2), 
                                                    Math.Round(totalCostOfOwn,2)));
        }
    }
}
