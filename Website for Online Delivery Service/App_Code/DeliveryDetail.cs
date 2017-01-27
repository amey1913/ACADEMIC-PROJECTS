using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;

/// <summary>
/// Summary description for DeliveryDetail
/// </summary>

public class DeliveryDetail
{
//   int accessCode; //These fields are matching
    DateTime requestDate;
    String pickupAddress; //with the fields in the
    String receipientAddress; //’New Delivery Details’ page.
    String receipientPhone;
    String description;

    public DeliveryDetail()
    {
    //    accessCode = 0; 
        
        pickupAddress = ""; 
        receipientAddress = "";
        receipientPhone = "";
        description = "";
    }

    /*
    public String AccessCode
    {
        get { return accessCode; }
        set { accessCode = value; }
    }
    */
    public DateTime RequestDate
    {
        get { return requestDate; }
        set { requestDate = value; }

    }
    public String PickupAddress
    {
        get { return pickupAddress; }
        set { pickupAddress = value; }
    }

    public String ReceipientAddress
    {
        get { return receipientAddress; }
        set { receipientAddress = value; }
    }

    public String ReceipientPhone
    {
        get { return receipientPhone; }
        set { receipientPhone = value; }
    }


    public String Description
    {
        get { return description; }
        set { description = value; }
    }

}