using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace ElevatorUI
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        int floor;
        int waitingPeople;
        int number;
        int capacity;
        double speed;


        public MainWindow()
        {
            InitializeComponent();
            SetSelectionAllOnGotFocus(Floors1);
            SetSelectionAllOnGotFocus(Wating_People1);
            SetSelectionAllOnGotFocus(Number1);
            SetSelectionAllOnGotFocus(Capacity1);
            SetSelectionAllOnGotFocus(Speed1);
        }

        private void OK_Button_Click(object sender, RoutedEventArgs e)
        {
            string strFloor = Floors1.Text;
            int.TryParse(strFloor, out floor);
            string strWaitingPeople = Wating_People1.Text;
            int.TryParse(strWaitingPeople, out waitingPeople);
            string strNumber = Number1.Text;
            int.TryParse(strNumber, out number);
            string strCapacity = Capacity1.Text;
            int.TryParse(strCapacity, out capacity);
            string strSpeed = Speed1.Text;
            double.TryParse(strSpeed, out speed);
            if (!Message(floor, number, capacity, waitingPeople, speed)) return;
            this.Close();
            WriteData(floor, number, capacity, waitingPeople, speed);
            Process.Start("ELevator.exe");
        }

        private void Cancel_Button_Click(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void SetSelectionAllOnGotFocus(TextBox textbox)
        {
            MouseButtonEventHandler _OnPreviewMouseDown = (sender, e) =>
            {
                TextBox box = e.Source as TextBox;
                box.Focus();
                e.Handled = true;
            };
            RoutedEventHandler _OnLostFocus = (sender, e) =>
            {
                TextBox box = e.Source as TextBox;
                box.PreviewMouseDown += _OnPreviewMouseDown;
            };
            RoutedEventHandler _OnGotFocus = (sender, e) =>
            {
                TextBox box = e.Source as TextBox;
                box.SelectAll();
                box.PreviewMouseDown -= _OnPreviewMouseDown;
            };

            textbox.PreviewMouseDown += _OnPreviewMouseDown;
            textbox.LostFocus += _OnLostFocus;
            textbox.GotFocus += _OnGotFocus;
        }

        private void WriteData(int floorNum, int elevatorNum, int elevatorWight, int peopleNum, double elevatorSpeed)
        {
            string path = ".\\Elevator_Data";
            FileStream fs = new FileStream(path, FileMode.Create);
            StreamWriter sw = new StreamWriter(fs);
            sw.Write(floorNum + "\n" + elevatorNum + "\n" + elevatorWight + "\n" + peopleNum + "\n" + elevatorSpeed + "\n");
            sw.Flush();
            sw.Close();
            fs.Close();
        }

        private bool Message(int floorNum, int elevatorNum, int elevatorWight, int peopleNum, double elevatorSpeed)
        {
            if (floorNum < 1 || floorNum > 1000)
            {
                var mes = MessageBox.Show($"Range of Floors: 1-1000!");
                return false;
            }
            if (peopleNum < 1 || peopleNum > 9999)
            {
                var mes = MessageBox.Show($"Range of Waiting People: 1-1000!");
                return false;
            }
            if (elevatorNum < 1 || elevatorNum > 10)
            {
                var mes = MessageBox.Show($"Range of Number: 1-10!");
                return false;
            }
            if (elevatorWight < 200 || elevatorWight > 999)
            {
                var mes = MessageBox.Show($"Range of Wight Capacity: 200-999!");
                return false;
            }
            if (elevatorSpeed < 1.0 || elevatorSpeed > 3.0)
            {
                var mes = MessageBox.Show($"Range of Speed: 1.0-3.0!");
                return false;
            }
            return true;
        }
    }
}
