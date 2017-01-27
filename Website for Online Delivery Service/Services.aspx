<%@ Page Language="C#" AutoEventWireup="true" CodeFile="Services.aspx.cs" Inherits="_Default" %>
<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Services</title>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <link href="StyleSheet.css" rel="stylesheet" type="text/css" />
    <script type="text/javascript" src="Contacts.js"></script>
</head>
<body onload ="loadDoc()">
    <form id="form1" runat="server">
        <table class ="Main_Table">
            <tr>
                <td colspan="2">
                     <img src ="Images/banner.png" class ="Banner_Img"/>
                </td>
            </tr>
            <tr>
                <td colspan="2">
                    <table class ="Nav">
                        <tr>
                            <td><a href="Default.aspx"><span>Home</span></a></td>
                            <td><a href="About.aspx"><span>About Us</span></a></td>
                            <td><a href="Services.aspx"><span>Services</span></a></td>
		                    <td><a href="Accounts.aspx"><span>Accounts</span></a></td>
		                    <td><a href="ContactUS.aspx"><span>Contact Us</span></a></td>
                            <td><a href="Resources.aspx"><span>Resources</span></a></td>
                            <td><a href="Service Area.aspx"><span>Service Areas</span></a></td>
                        </tr>
                    </table>

                </td>
            </tr>
            <tr>
                <td>
                    <table style="width:100%; height:100%; border:groove" border ="1" >
                        <tr>
                            <td class ="Adv_1">
                                 <div id="phoneDetails"></div>
                            </td>
                        </tr>
                        <tr>
                            <td class="Adv_2">
                                <img src ="Images/credit_cards.png"/>
                            </td>
                        </tr>
                    </table>
                </td>
                <td>
                    <table style="width:100%; height:100%" class="Service_Text">
                       <tr>
                            <td colspan = "2">
                                
                                <h1>Services</h1>
                                
                                <p>T & P Delivery Services is geared to meet a variety of challenges that your same day
                                 shipping needs might present. We have the knowledge and experience to set up programs to
                                 specifically meet or exceed both you and your client's expectations of service, quality
                                 and on-time dependability. </p>  
                            </td>
                        </tr>
                        <tr>
                            <td>
                                <h3>Here are a few of the specialized programs we offer:</h3>
                                <ul style ="padding-left:200px">
                                    <li>Grocery Delivery</li>
                                    <li>Medical Deliveries</li>
                                    <li>Legal Courier Deliveries</li>
                                </ul>
                            </td>
                            <td style="background-color:#ffffff; background-image:url('Images/Parcel_delivery.png'); background-size: 100% 110%; padding-right:100px">
                            </td> 
                        </tr>
                        <tr>
                            <td colspan ="2">                        
                                <p>Each type of service is unique in its specific requirements of service and commitments and each is understood by our staff
                                of trained professionals. our commitment of 24 hours a day reliability to our clients is unsurpassed. Our performance is one
                                you can count on immediately!</p>
                            </td>
                        </tr>
                    </table>
                </td>
            </tr>             
        </table>
    </form>
</body>
</html>
