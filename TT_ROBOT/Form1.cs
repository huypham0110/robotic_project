using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;

namespace TT_ROBOT
{
    public partial class Form1 : Form
    {
        int L1 = 65, L2 = 170, L3 = 110;

        String theta2_dd_1Str, theta2_dd_2Str, theta2_dd_3Str, theta2_dd_4Str, theta2_dd_5Str, theta2_dd_6Str;
        public Form1()
        {
            InitializeComponent();
            String[] Baudrate = { "1200", "2400", "4800", "9600", "115200" };
            cbBaudrate.Items.AddRange(Baudrate);
            Control.CheckForIllegalCrossThreadCalls = false;
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            cbPort.DataSource = SerialPort.GetPortNames();
            cbBaudrate.Text = "115200";


            
        }

        private void butConnect_Click(object sender, EventArgs e)
        {
            if (!seCOM.IsOpen)
            {
                seCOM.PortName = cbPort.Text;
                seCOM.BaudRate = Convert.ToInt32(cbBaudrate.Text);
                seCOM.Open();

                labStatus.Text = "Connected!";
                labStatus.ForeColor = Color.DarkGreen;
            }
        }

        private void butDisconnect_Click(object sender, EventArgs e)
        {
            seCOM.Close();
            labStatus.Text = "Disconnected!";
            labStatus.ForeColor = Color.Red;
        }

        private void butHome_Click(object sender, EventArgs e)
        {
            if (!seCOM.IsOpen)
                MessageBox.Show("Chưa kết nối cổng Serial");
            else
            {
                seCOM.Write("home");

                txtiPx_1.Text = "345";
                txtiPy_1.Text = "0";
                txtiPz_1.Text = "0";

                txtiPx_2.Text = "345";
                txtiPy_2.Text = "0";
                txtiPz_2.Text = "0";

                txtiPx_3.Text = "345";
                txtiPy_3.Text = "0";
                txtiPz_3.Text = "0";

                txtiPx_4.Text = "345";
                txtiPy_4.Text = "0";
                txtiPz_4.Text = "0";

                txtiPx_5.Text = "345";
                txtiPy_5.Text = "0";
                txtiPz_5.Text = "0";

                txtiPx_6.Text = "345";
                txtiPy_6.Text = "0";
                txtiPz_6.Text = "0";
                labData.Text ="home";
            }
        }

        private void seCOM_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            String dataReceive = seCOM.ReadExisting();

        }

        private void butResetInverse_Click(object sender, EventArgs e)
        {

            txtiPx_1.Text = "345";
            txtiPy_1.Text = "0";
            txtiPz_1.Text = "0";

            txtiPx_2.Text = "345";
            txtiPy_2.Text = "0";
            txtiPz_2.Text = "0";

            txtiPx_3.Text = "345";
            txtiPy_3.Text = "0";
            txtiPz_3.Text = "0";

            txtiPx_4.Text = "345";
            txtiPy_4.Text = "0";
            txtiPz_4.Text = "0";

            txtiPx_5.Text = "345";
            txtiPy_5.Text = "0";
            txtiPz_5.Text = "0";

            txtiPx_6.Text = "345";
            txtiPy_6.Text = "0";
            txtiPz_6.Text = "0";

        }


        private void butSetInverse_Click(object sender, EventArgs e)
        {
            String dataSend;
            if (txtid_1.Text == "" || txtiTheta1_1.Text == "" || txtiTheta2_1.Text == "" ||
                txtid_2.Text == "" || txtiTheta1_2.Text == "" || txtiTheta2_2.Text == "" ||
                txtid_3.Text == "" || txtiTheta1_3.Text == "" || txtiTheta2_3.Text == "" ||
                txtid_4.Text == "" || txtiTheta1_4.Text == "" || txtiTheta2_4.Text == "" ||
                txtid_5.Text == "" || txtiTheta1_5.Text == "" || txtiTheta2_5.Text == "" ||
                txtid_6.Text == "" || txtiTheta1_6.Text == "" || txtiTheta2_6.Text == "" )
            {
                MessageBox.Show("Vui lòng nhập giá trị các thông số của robot");
            }
            else
            {
                dataSend = soluong.Text + ','   + txtid_6.Text + ',' + txtiTheta1_6.Text + ',' + theta2_dd_6Str + ','
                                                + txtid_1.Text + ',' + txtiTheta1_1.Text + ',' + theta2_dd_1Str + ','
                                                + txtid_2.Text + ',' + txtiTheta1_2.Text + ',' + theta2_dd_2Str + ','
                                                + txtid_3.Text + ',' + txtiTheta1_3.Text + ',' + theta2_dd_3Str + ','
                                                + txtid_4.Text + ',' + txtiTheta1_4.Text + ',' + theta2_dd_4Str + ','
                                                + txtid_5.Text + ',' + txtiTheta1_5.Text + ',' + theta2_dd_5Str + ',';
                labData.Text = dataSend;
                seCOM.Write(dataSend);
            }
        }

        private void butInverse_Click(object sender, EventArgs e)
        {
            // Toạ độ 1
            double x_1, y_1, z_1, theta1_1, theta2_1, c2_1, s2_1, c1_1, s1_1, theta1_d_1, theta2_d_1, theta2_dd_1;
            x_1 = (double)Convert.ToInt32(txtiPx_1.Text);
            y_1 = (double)Convert.ToInt32(txtiPy_1.Text);
            z_1 = (double)Convert.ToInt32(txtiPz_1.Text);
            // tìm theta 2
            c2_1 = ((x_1 - L1) * (x_1 - L1) + y_1 * y_1 - L3 * L3 - L2 * L2) / (2 * L2 * L3);
            s2_1 = Math.Sqrt(1 - c2_1 * c2_1);
            theta2_1 = Math.Atan2(s2_1, c2_1);
            //tìm theta 1
            c1_1 = ((x_1 - L1) * (L3 * Math.Cos(theta2_1) + L2) + y_1 * L3 * Math.Sin(theta2_1)) / ((L3 * Math.Cos(theta2_1) + L2) * (L3 * Math.Cos(theta2_1) + L2) + (L3 * Math.Sin(theta2_1)) * (L3 * Math.Sin(theta2_1)));
            s1_1 = ((L3 * Math.Cos(theta2_1) + L2) * y_1 - (x_1 - L1) * L3 * Math.Sin(theta2_1)) / ((L3 * Math.Cos(theta2_1) + L2) * (L3 * Math.Cos(theta2_1) + L2) + (L3 * Math.Sin(theta2_1)) * (L3 * Math.Sin(theta2_1)));
            theta1_1 = Math.Atan2(s1_1, c1_1);
            theta1_d_1 = theta1_1 * 180 / Math.PI;
            theta2_d_1 = theta2_1 * 180 / Math.PI;
            theta2_d_1 = Math.Round(theta2_d_1, 2);
            theta1_d_1 = Math.Round(theta1_d_1, 2);
            theta2_dd_1 = theta2_d_1 + theta1_d_1; // theta2_d thực
            theta2_dd_1Str = theta2_dd_1.ToString();
            txtiTheta1_1.Text = theta1_d_1.ToString();
            txtiTheta2_1.Text = theta2_d_1.ToString();
            
            txtid_1.Text = z_1.ToString();

            // Toạ độ 2
            double x_2, y_2, z_2, theta1_2, theta2_2, c2_2, s2_2, c1_2, s1_2, theta1_d_2, theta2_d_2, theta2_dd_2;
            x_2 = (double)Convert.ToInt32(txtiPx_2.Text);
            y_2 = (double)Convert.ToInt32(txtiPy_2.Text);
                z_2 = (double)Convert.ToInt32(txtiPz_2.Text);
            // tìm theta 2
            c2_2 = ((x_2 - L1) * (x_2 - L1) + y_2 * y_2 - L3 * L3 - L2 * L2) / (2 * L2 * L3);
            s2_2 = Math.Sqrt(1 - c2_2 * c2_2);
            theta2_2 = Math.Atan2(s2_2, c2_2);
            //tìm theta 1
            c1_2 = ((x_2 - L1) * (L3 * Math.Cos(theta2_2) + L2) + y_2 * L3 * Math.Sin(theta2_2)) / ((L3 * Math.Cos(theta2_2) + L2) * (L3 * Math.Cos(theta2_2) + L2) + (L3 * Math.Sin(theta2_2)) * (L3 * Math.Sin(theta2_2)));
            s1_2 = ((L3 * Math.Cos(theta2_2) + L2) * y_2 - (x_2 - L1) * L3 * Math.Sin(theta2_2)) / ((L3 * Math.Cos(theta2_2) + L2) * (L3 * Math.Cos(theta2_2) + L2) + (L3 * Math.Sin(theta2_2)) * (L3 * Math.Sin(theta2_2)));
            theta1_2 = Math.Atan2(s1_2, c1_2);
            theta1_d_2 = theta1_2 * 180 / Math.PI;
            theta2_d_2 = theta2_2 * 180 / Math.PI;
            theta2_d_2 = Math.Round(theta2_d_2, 2);
            theta1_d_2 = Math.Round(theta1_d_2, 2);
            theta2_dd_2 = theta2_d_2 + theta1_d_2; // theta2_d thực
            theta2_dd_2Str = theta2_dd_2.ToString();
            txtiTheta1_2.Text = theta1_d_2.ToString();
            txtiTheta2_2.Text = theta2_d_2.ToString();
            txtid_2.Text = z_2.ToString();

            // Toạ độ 3
            double x_3, y_3, z_3, theta1_3, theta2_3, c2_3, s2_3, c1_3, s1_3, theta1_d_3, theta2_d_3, theta2_dd_3;
            x_3 = (double)Convert.ToInt32(txtiPx_3.Text);
            y_3 = (double)Convert.ToInt32(txtiPy_3.Text);
            z_3 = (double)Convert.ToInt32(txtiPz_3.Text);
            // tìm theta 2
            c2_3 = ((x_3 - L1) * (x_3 - L1) + y_3 * y_3 - L3 * L3 - L2 * L2) / (2 * L2 * L3);
            s2_3 = Math.Sqrt(1 - c2_3 * c2_3);
            theta2_3 = Math.Atan2(s2_3, c2_3);
            //tìm theta 1
            c1_3 = ((x_3 - L1) * (L3 * Math.Cos(theta2_3) + L2) + y_3 * L3 * Math.Sin(theta2_3)) / ((L3 * Math.Cos(theta2_3) + L2) * (L3 * Math.Cos(theta2_3) + L2) + (L3 * Math.Sin(theta2_3)) * (L3 * Math.Sin(theta2_3)));
            s1_3 = ((L3 * Math.Cos(theta2_3) + L2) * y_3 - (x_3 - L1) * L3 * Math.Sin(theta2_3)) / ((L3 * Math.Cos(theta2_3) + L2) * (L3 * Math.Cos(theta2_3) + L2) + (L3 * Math.Sin(theta2_3)) * (L3 * Math.Sin(theta2_3)));
            theta1_3 = Math.Atan2(s1_3, c1_3);
            theta1_d_3 = theta1_3 * 180 / Math.PI;
            theta2_d_3 = theta2_3 * 180 / Math.PI;
            theta2_d_3 = Math.Round(theta2_d_3, 2);
            theta1_d_3 = Math.Round(theta1_d_3, 2);
            theta2_dd_3 = theta2_d_3 + theta1_d_3; // theta2_d thực
            theta2_dd_3Str = theta2_dd_3.ToString();
            theta2_dd_1Str = theta2_dd_1.ToString();
            txtiTheta1_3.Text = theta1_d_3.ToString();
            txtiTheta2_3.Text = theta2_d_3.ToString();

            txtid_3.Text = z_3.ToString();

            // Toạ độ 4
            double x_4, y_4, z_4, theta1_4, theta2_4, c2_4, s2_4, c1_4, s1_4, theta1_d_4, theta2_d_4, theta2_dd_4;
            x_4 = (double)Convert.ToInt32(txtiPx_4.Text);
            y_4 = (double)Convert.ToInt32(txtiPy_4.Text);
            z_4 = (double)Convert.ToInt32(txtiPz_4.Text);
            // tìm theta 2
            c2_4 = ((x_4 - L1) * (x_4 - L1) + y_4 * y_4 - L3 * L3 - L2 * L2) / (2 * L2 * L3);
            s2_4 = Math.Sqrt(1 - c2_4 * c2_4);
            theta2_4 = Math.Atan2(s2_4, c2_4);
            //tìm theta 1
            c1_4 = ((x_4 - L1) * (L3 * Math.Cos(theta2_4) + L2) + y_4 * L3 * Math.Sin(theta2_4)) / ((L3 * Math.Cos(theta2_4) + L2) * (L3 * Math.Cos(theta2_4) + L2) + (L3 * Math.Sin(theta2_4)) * (L3 * Math.Sin(theta2_4)));
            s1_4 = ((L3 * Math.Cos(theta2_4) + L2) * y_4 - (x_4 - L1) * L3 * Math.Sin(theta2_4)) / ((L3 * Math.Cos(theta2_4) + L2) * (L3 * Math.Cos(theta2_4) + L2) + (L3 * Math.Sin(theta2_4)) * (L3 * Math.Sin(theta2_4)));
            theta1_4 = Math.Atan2(s1_4, c1_4);
            theta1_d_4 = theta1_4 * 180 / Math.PI;
            theta2_d_4 = theta2_4 * 180 / Math.PI;
            theta2_d_4 = Math.Round(theta2_d_4, 2);
            theta1_d_4 = Math.Round(theta1_d_4, 2);
            theta2_dd_4 = theta2_d_4 + theta1_d_4; // theta2_d thực
            theta2_dd_4Str = theta2_dd_4.ToString();
            txtiTheta1_4.Text = theta1_d_4.ToString();
            txtiTheta2_4.Text = theta2_d_4.ToString();
            txtid_4.Text = z_4.ToString();

            // Toạ độ 5
            double x_5, y_5, z_5, theta1_5, theta2_5, c2_5, s2_5, c1_5, s1_5, theta1_d_5, theta2_d_5, theta2_dd_5;
            x_5 = (double)Convert.ToInt32(txtiPx_5.Text);
            y_5 = (double)Convert.ToInt32(txtiPy_5.Text);
            z_5 = (double)Convert.ToInt32(txtiPz_5.Text);
            // tìm theta 2
            c2_5 = ((x_5 - L1) * (x_5 - L1) + y_5 * y_5 - L3 * L3 - L2 * L2) / (2 * L2 * L3);
            s2_5 = Math.Sqrt(1 - c2_5 * c2_5);
            theta2_5 = Math.Atan2(s2_5, c2_5);
            //tìm theta 1
            c1_5 = ((x_5 - L1) * (L3 * Math.Cos(theta2_5) + L2) + y_5 * L3 * Math.Sin(theta2_5)) / ((L3 * Math.Cos(theta2_5) + L2) * (L3 * Math.Cos(theta2_5) + L2) + (L3 * Math.Sin(theta2_5)) * (L3 * Math.Sin(theta2_5)));
            s1_5 = ((L3 * Math.Cos(theta2_5) + L2) * y_5 - (x_5 - L1) * L3 * Math.Sin(theta2_5)) / ((L3 * Math.Cos(theta2_5) + L2) * (L3 * Math.Cos(theta2_5) + L2) + (L3 * Math.Sin(theta2_5)) * (L3 * Math.Sin(theta2_5)));
            theta1_5 = Math.Atan2(s1_5, c1_5);
            theta1_d_5 = theta1_5 * 180 / Math.PI;
            theta2_d_5 = theta2_5 * 180 / Math.PI;
            theta2_d_5 = Math.Round(theta2_d_5, 2);
            theta1_d_5 = Math.Round(theta1_d_5, 2);
            theta2_dd_5 = theta2_d_5 + theta1_d_5; // theta2_d thực
            theta2_dd_5Str = theta2_dd_5.ToString();
            txtiTheta1_5.Text = theta1_d_5.ToString();
            txtiTheta2_5.Text = theta2_d_5.ToString();
            txtid_5.Text = z_5.ToString();

            // Toạ độ 6
            double x_6, y_6, z_6, theta1_6, theta2_6, c2_6, s2_6, c1_6, s1_6, theta1_d_6, theta2_d_6, theta2_dd_6;
            x_6 = (double)Convert.ToInt32(txtiPx_6.Text);
            y_6 = (double)Convert.ToInt32(txtiPy_6.Text);
            z_6 = (double)Convert.ToInt32(txtiPz_6.Text);
            // tìm theta 2
            c2_6 = ((x_6 - L1) * (x_6 - L1) + y_6 * y_6 - L3 * L3 - L2 * L2) / (2 * L2 * L3);
            s2_6 = Math.Sqrt(1 - c2_6 * c2_6);
            theta2_6 = Math.Atan2(s2_6, c2_6);
            //tìm theta 1
            c1_6 = ((x_6 - L1) * (L3 * Math.Cos(theta2_6) + L2) + y_6 * L3 * Math.Sin(theta2_6)) / ((L3 * Math.Cos(theta2_6) + L2) * (L3 * Math.Cos(theta2_6) + L2) + (L3 * Math.Sin(theta2_6)) * (L3 * Math.Sin(theta2_6)));
            s1_6 = ((L3 * Math.Cos(theta2_6) + L2) * y_6 - (x_6 - L1) * L3 * Math.Sin(theta2_6)) / ((L3 * Math.Cos(theta2_6) + L2) * (L3 * Math.Cos(theta2_6) + L2) + (L3 * Math.Sin(theta2_6)) * (L3 * Math.Sin(theta2_6)));
            theta1_6 = Math.Atan2(s1_6, c1_6);
            theta1_d_6 = theta1_6 * 180 / Math.PI;
            theta2_d_6 = theta2_6 * 180 / Math.PI;
            theta2_d_6 = Math.Round(theta2_d_6, 2);
            theta1_d_6 = Math.Round(theta1_d_6, 2);
            theta2_dd_6 = theta2_d_6 + theta1_d_6; // theta2_d thực
            theta2_dd_6Str = theta2_dd_6.ToString();
            txtiTheta1_6.Text = theta1_d_6.ToString();
            txtiTheta2_6.Text = theta2_d_6.ToString();
            txtid_6.Text = z_6.ToString();
        }
    }
}
