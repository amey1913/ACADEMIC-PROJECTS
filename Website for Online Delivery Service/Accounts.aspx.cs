using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Net.Mail;
using System.Net;
using System.Data;
using System.Data.SqlClient;
using System.Configuration;


public partial class _Default : System.Web.UI.Page
{

    protected void Page_Load(object sender, EventArgs e)
    {
        if (Session["CurrentUser"] == null)
        {
            login_users.Visible = true;
            current_users_panel.Visible = true;
            new_users_panel.Visible = false;
            user_account_panel.Visible = false;
            recover_password.Visible = false;
        }
        else
        {
            login_users.Visible = false;
            current_users_panel.Visible = false;
            new_users_panel.Visible = false;
            user_account_panel.Visible = true;
            recover_password.Visible = false;
        }

    }
    
    protected void accountIndexChanged(object sender, EventArgs e)
    {
        if (string.Equals(New_Current_Users.SelectedValue, "current_users"))
        {
            current_users_panel.Visible = true;
            new_users_panel.Visible = false;
        }
        else
        {
            current_users_panel.Visible = false;
            new_users_panel.Visible = true;
        }
    }

    protected Boolean check_Existing_User(List<User> allUsersList, String email)
    {
        for( int i = 0; i < allUsersList.Count ; i++)
        {
            if(allUsersList[i].EmailAddress.Equals(email))
            {
                return true;
            }
        }
        return false;
    }

    protected int check_Valid_User_Login(List<User> allUsersList, String email, String code)
    {
        for (int i = 0; i < allUsersList.Count; i++)
        {
            if (allUsersList[i].EmailAddress.Equals(email) && Int32.Parse(code) == allUsersList[i].AccessCode)
            {
                return i;
            }
        }
        return -1;
    }

    protected void login_B_Click(object sender, EventArgs e)
    {
        RequiredFieldValidator1.Validate();
        RegularExpressionValidator1.Validate();
        RequiredFieldValidator2.Validate();
        RegularExpressionValidator2.Validate();

        if (RequiredFieldValidator1.IsValid == false ||
            RegularExpressionValidator1.IsValid == false ||
            RequiredFieldValidator2.IsValid == false ||
            RegularExpressionValidator2.IsValid == false)
        {
            return;
        }

        String email = email_T.Text;
        String code = password_T.Text;
        int current_User_Index = -1;
        List<User> allUsersList = Application["AllUsersList"] as List<User>;

        if ((Application["AllUsersList"] != null) && (current_User_Index = check_Valid_User_Login(allUsersList, email, code)) >= 0)
        {

            ScriptManager.RegisterClientScriptBlock(this, typeof(Page), "", "alert('Successpully Logged In!');", true);

            Session["CurrentUser"] = allUsersList[current_User_Index];

            login_L1.Text = "Welcome " + allUsersList[current_User_Index].FullName + " !";

            login_users.Visible = false;
            current_users_panel.Visible = false;
            new_users_panel.Visible = false;
            user_account_panel.Visible = true;
            recover_password.Visible = false;
        }
        else
        {
            ScriptManager.RegisterClientScriptBlock(this, typeof(Page), "", "alert('Unable to Login. Invalid email-id or access-code!');", true);

        }
    }


    protected void update_Welcome_lable(object sender, EventArgs e)
    {
        if (Session["CurrentUser"] != null)
        {
            User aUser = Session["CurrentUser"] as User;

            login_L1.Text = "Welcome " + aUser.FullName + " !";
        }
    }

    protected void reover_link_Click(object sender, EventArgs e)
    {
        login_users.Visible = false;
        current_users_panel.Visible = false;
        new_users_panel.Visible = false;
        user_account_panel.Visible = false;
        recover_password.Visible = true;
    }

    protected void recover_button_click(object sender, EventArgs e)
    {
        RegularExpressionValidator3.Validate();
        RequiredFieldValidator3.Validate();
        
        if (RegularExpressionValidator3.IsValid == false ||
            RequiredFieldValidator3.IsValid == false)
        {
            login_users.Visible = false;
            current_users_panel.Visible = false;
            new_users_panel.Visible = false;
            user_account_panel.Visible = false;
            recover_password.Visible = true;

            return;
        }

        String messageString = "";

        List<User> allUsersList = Application["AllUsersList"] as List<User>;
        String email_id = email_T2.Text;

        int tempAccessCode = 0;

        if ((Application["AllUsersList"] != null) && (check_Existing_User(allUsersList, email_id)))
        { 
         
                
                for (int i = 0; i < allUsersList.Count; i++)
                {
                    if (allUsersList[i].EmailAddress.Equals(email_id))
                    {
                        // get accessCode from the database
                        String connStr = ConfigurationManager.ConnectionStrings["connectionString"].ConnectionString;
                        SqlConnection conn = new SqlConnection(connStr);

                        String select = "select accessCode from ParabA2_WADsp16_users" + 
                                                            " where emailAddress = '" +
                                                             allUsersList[i].EmailAddress + "'";
                        SqlCommand command = new SqlCommand(select, conn);


                        try
                        {
                            conn.Open();
                            SqlDataReader sqlReader = command.ExecuteReader();
                            while (sqlReader.Read())
                            {
                                tempAccessCode = (int)sqlReader["accessCode"];
                            }
                            String header = "Recover Password";
                            String subject = "We have recovered your Access Code!";
                            String body = "Valued Customer,<br/>Thank you for contacting us. Your access code is " + tempAccessCode.ToString() + ".<br/>Thank You.<br/><br/>T & P Delivery Service – Security Team";
                            if (send_mail_to_user(allUsersList[i].EmailAddress, header, subject, body))
                            {
                                messageString = "alert('Your Access code has been sent to the email address in file');";
                            }

                        }
                        finally
                        {
                            conn.Close();
                        }
                        break;
                    }
                }
                
                //send email logic
                login_users.Visible = true;
                current_users_panel.Visible = true;
                new_users_panel.Visible = false;
                user_account_panel.Visible = false;
                recover_password.Visible = false;
            
        }
        else
        {
            messageString = "alert('Sorry Your Email Account cannot be verified');";
            login_users.Visible = false;
            current_users_panel.Visible = false;
            new_users_panel.Visible = false;
            user_account_panel.Visible = false;
            recover_password.Visible = true;
        }

        ScriptManager.RegisterClientScriptBlock(this, typeof(Page), "", messageString, true);
    }

    protected void getAccessCode(object sender, EventArgs e)
    {
        Random gen = new Random();
        String rand_no = gen.Next(100000, 999999).ToString("D6");
        acc_code_T.Text = rand_no;
    }
    protected void no_thanks_L_Click(object sender, EventArgs e)
    {
        Response.Redirect("Accounts.aspx");
    }

    protected void submitReq_Click(object sender, EventArgs e)
    {
        RequiredFieldValidator11.Validate();
        RequiredFieldValidator10.Validate();
        RequiredFieldValidator9.Validate();
        RegularExpressionValidator6.Validate();
        RequiredFieldValidator12.Validate();

        if(RequiredFieldValidator11.IsValid == false ||
            RequiredFieldValidator10.IsValid == false ||
            RequiredFieldValidator9.IsValid == false ||
            RegularExpressionValidator6.IsValid == false ||
            RequiredFieldValidator12.IsValid == false)
        {
            return;
        }

        var pickup_Address = loginT1.Text;
        var recipient_Address = loginT2.Text;
        var recipient_phone = loginT3.Text;
        var description = loginT4.Text;

        DeliveryDetail d = new DeliveryDetail();
        User aUser = Session["CurrentUser"] as User;

        d.PickupAddress = pickup_Address;
        d.ReceipientAddress = recipient_Address;
        d.ReceipientPhone = recipient_phone;
        d.Description = description;

        aUser.DeliveryDetailsList.Add(d);
        // Storing into table Delivery Request.
        String connStr = ConfigurationManager.ConnectionStrings["connectionString"].ConnectionString;
        SqlConnection conn = new SqlConnection(connStr);

        String insert = "Insert into ParabA2_WADsp16_delivery_request(accessCode, pickupAddress, receipientAddress, receipientPhone, description) " +
                                "values(" + aUser.AccessCode + ", '" +
                                            pickup_Address + "', '" +
                                            recipient_Address + "', '" +
                                            recipient_phone + "', '" +
                                            description + "')";
        SqlCommand command = new SqlCommand(insert, conn);
        

        try
        {
            conn.Open();
            command.BeginExecuteNonQuery();

        }
        finally
        {
            conn.Close();
        }

        String header = "Delivery Request";
        String subject = "T & P Delivery Service - New Request Confirmation";
        String body = "Valued Customer " + aUser.FullName + ",<br/>You have requested a new delivery. Details shown below. <br/> <br/>" +
                      "Pickup Address : " + d.PickupAddress + "<br/>" +
                      "Recipient Address : " + d.ReceipientAddress + "<br/>" +
                      "Description : " + d.Description + "<br/><br/>" +
                      "Please note that any modifications made after 2 hours of submission of the original request shall be rejected.<br/><br/>" +
                      "Thank You again for keeping trust on us.<br/><br/>T & P Delivery Service Team";

        String email = aUser.EmailAddress;
        if (send_mail_to_user(email, header, subject, body))
        {

            ScriptManager.RegisterClientScriptBlock(this, typeof(Page), "", "alert('Thank You for submitting a delivery request." +
            " We are more than happy to serve you. An invoice email has been sent to the email address in our file');", true);
        }
        

        Session["CurrentUser"] = aUser;

        login_users.Visible = false;
        current_users_panel.Visible = false;
        new_users_panel.Visible = false;
        user_account_panel.Visible = true;
        recover_password.Visible = false;
    }

    protected void create_account_L_Click(object sender, EventArgs e)
    {
        RequiredFieldValidator4.Validate();
        RequiredFieldValidator5.Validate();
        RequiredFieldValidator6.Validate();
        RegularExpressionValidator4.Validate();
        RequiredFieldValidator7.Validate();
        RegularExpressionValidator5.Validate();
        RequiredFieldValidator8.Validate();
        newTextComp7.Validate();

        if (RequiredFieldValidator4.IsValid == false ||
            RequiredFieldValidator5.IsValid == false ||
            RequiredFieldValidator6.IsValid == false ||
            RegularExpressionValidator4.IsValid == false ||
            RegularExpressionValidator5.IsValid == false ||
            RequiredFieldValidator7.IsValid == false ||
            RequiredFieldValidator8.IsValid == false ||
            newTextComp7.IsValid == false)
        {

            login_users.Visible = true;
            current_users_panel.Visible = false;
            new_users_panel.Visible = true;
            user_account_panel.Visible = false;
            recover_password.Visible = false;
            New_Current_Users.SelectedIndex = 1;
            return;
        }

        List<User> allUsersList = Application["AllUsersList"] as List<User>;

        String name = name_T.Text;
        String company = company_T.Text;
        String address = addr_T.Text;
        String phone = phone_T.Text;
        String email_id = email_id_T.Text;
        int code_system =  Int32.Parse(acc_code_T.Text);
        int code =  Int32.Parse(code_T.Text);

        if ((Application["AllUsersList"] != null) && (check_Existing_User(allUsersList, email_id)))
        {
            ScriptManager.RegisterClientScriptBlock(this, typeof(Page), "", "alert('Your Email-Address is already registered in our database. Please Login!');", true);

            login_users.Visible = true;
            current_users_panel.Visible = false;
            new_users_panel.Visible = true;
            user_account_panel.Visible = false;
            recover_password.Visible = false;
            New_Current_Users.SelectedIndex = 1;
            return;
        }
        else
        {    
            User aUser = new User();
            
            aUser.FullName = name;
            aUser.Company = company;
            aUser.MailingAddress = address;
            aUser.PhoneNumber = phone;
            aUser.EmailAddress = email_id;
            aUser.AccessCode = code;

            allUsersList.Add(aUser);
            Application["AllUsersList"] = allUsersList;
            
            // Storing into table Users.
            String connStr = ConfigurationManager.ConnectionStrings["connectionString"].ConnectionString;
            SqlConnection conn = new SqlConnection(connStr);
            
            String insert = "Insert into ParabA2_WADsp16_users(accessCode, fullName, company, mailingAddress, phoneNumber, emailAddress) " +
                                    "values(" + code + ", '" +
                                                name + "', '" +
                                                company + "', '" +
                                                address + "', '" +
                                                phone + "', '" +
                                                email_id + "')";
            SqlCommand command = new SqlCommand(insert, conn);

            //SqlTransaction trans = conn.BeginTransaction("User_trans");
            try
            {
                conn.Open();
                command.BeginExecuteNonQuery();

            }
            finally
            {
                //trans.Commit();
                conn.Close();
            }
                
            String header = "Registeration";
            String subject = "T & P Delivery Service - Registration Confirmation";
            String body = "Valued Customer " + aUser.FullName + ",<br/>Thank you for registering with T & P Delivery Service Name. You can now start using your account to " +
                                                                "request us to deliver your goods.<br/><br/>" +
                                                                "Looking forward to business with you.<br/>" +
                                                                "Thank You again for keeping trust on us.<br/><br/>T & P Delivery Service – Security Team";
            if (send_mail_to_user(aUser.EmailAddress, header, subject, body))
            {
                ScriptManager.RegisterClientScriptBlock(this, typeof(Page), "", "alert('Thank You for registering. You can now Login!');", true);

                login_users.Visible = true;
                current_users_panel.Visible = true;
                new_users_panel.Visible = false;
                user_account_panel.Visible = false;
                recover_password.Visible = false;
                New_Current_Users.SelectedIndex = 0;
            }
        }      
    }
    protected void log_out_Click(object sender, EventArgs e)
    {
        User aUser = Session["CurrentUser"] as User;

        int current_User_Index = -1;
        List<User> allUsersList = Application["AllUsersList"] as List<User>;

        if ((Application["AllUsersList"] != null) && (current_User_Index = check_Valid_User_Login(allUsersList, aUser.EmailAddress, aUser.AccessCode.ToString())) >= 0)
        {
            allUsersList[current_User_Index] = aUser;
            Application["AllUsersList"] = allUsersList;
               
            Session.Abandon();
            ScriptManager.RegisterClientScriptBlock(this, typeof(Page), "", "alert('Successfully Logged Out!');window.location='Accounts.aspx'", true);

        }
    }

    public bool send_mail_to_user(String email, String header, String subject, String body)
    {
        System.Net.Mail.MailMessage mail = new System.Net.Mail.MailMessage();
        mail.To.Add(email);
        mail.From = new MailAddress("amey.1913@gmail.com", header, System.Text.Encoding.UTF8);
        mail.Subject = subject;
        mail.SubjectEncoding = System.Text.Encoding.UTF8;
        mail.Body = body;
        mail.BodyEncoding = System.Text.Encoding.UTF8;
        mail.IsBodyHtml = true;
        mail.Priority = MailPriority.High;
        SmtpClient client = new SmtpClient();
        client.Credentials = new System.Net.NetworkCredential("amey.1913@gmail.com", "amey_9773");
        client.Port = 587;
        client.Host = "smtp.gmail.com";
        client.EnableSsl = true;
        try
        {
            client.Send(mail);
            return true;

        }
        catch (Exception ex)
        {
            Exception ex2 = ex;
            string errorMessage = string.Empty;
            while (ex2 != null)
            {
                errorMessage += ex2.ToString();
                ex2 = ex2.InnerException;
            }
        }
        return false;
    }

}