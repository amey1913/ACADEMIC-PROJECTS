using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

/// <summary>
/// Summary description for User
/// </summary>
public class User
{
    String fullName;
    String company;
    String mailingAddress;
    String phoneNumber;
    String emailAddress;
    int accessCode;
    List<DeliveryDetail> deliveryDetailsList;

    public User()
    {
        fullName = "";
        company = "";
        mailingAddress = "";
        phoneNumber = "";
        emailAddress = "";
        accessCode = 0;
        deliveryDetailsList = new List<DeliveryDetail>(); 
    }

    public String FullName //This is a property to the name field.
    {
        get { return fullName; }
        set { fullName = value; }
    }

    public String Company //This is a property to the company field.
    {
        get { return company; }
        set { company = value; }
    }

    public String MailingAddress //This is a mailingAddress to the company field.
    {
        get { return mailingAddress; }
        set { mailingAddress = value; }
    }
    public String PhoneNumber //This is a phoneNumber to the company field.
    {
        get { return phoneNumber; }
        set { phoneNumber = value; }
    }
    public String EmailAddress //This is a property to the emailAddress field.
    {
        get { return emailAddress; }
        set { emailAddress = value; }
    }
    public int AccessCode //This is a property to the accessCode field.
    {
        get { return accessCode; }
        set { accessCode = value; }
    }
    public List<DeliveryDetail> DeliveryDetailsList //This is a property to the deliveryDetailsList field.
    {
        get { return deliveryDetailsList; }
    }    

}