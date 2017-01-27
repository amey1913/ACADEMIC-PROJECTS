using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Net.Mail;

public partial class _Default : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {

    }
    protected void submitMesage(object sender, EventArgs e)
    {
        String email = emailText.Text;
       
        if (!ValidateEmail())
        {
            return;
        }

        String header = "Acknowledgement";
        String subject = "We have received your message!";
        String body = "Valued Customer,<br/>Thank you for contacting us. One of our customer service representatives will be contacting you within the next 24 hours.<br/><br/>T & P Delivery Service – Customer Service Team";
        if (send_email(email, header, subject, body))
        {
            ScriptManager.RegisterClientScriptBlock(this, this.GetType(), "", "alert('Your Message has been sent to our Customer Service Team')", true);
        }
        else
        {
            ScriptManager.RegisterClientScriptBlock(this, this.GetType(), "", "alert('We could not submit your request at this time.')", true);
        }
    }

    private bool ValidateEmail()
    {
        validEmailReq.Validate();
        validEmailReg.Validate();
        validMsgreq.Validate();

        if (!validEmailReq.IsValid || !validEmailReg.IsValid || !validMsgreq.IsValid)
        {
            return false;
        }
        return true;
    }

    public bool send_email(String email, String header, String subject, String body)
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