<%@ Page Language="C#" AutoEventWireup="true" CodeFile="Service Area.aspx.cs" Inherits="_Default" %>
<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Service Areas</title>
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
                    <table style="width:100%; height:100%; border:groove" border ="1" >
                    <tr>
                    <td>
                    <table style="width:100%; height:100% " class="Contact_Text">
                       <tr>
                            <td>
                                <h1>Service Areas</h1>
                                
                                <p>T & P Delivery Service is your Demand Specialist and your Instant Solution to your 
                                    same day shipping needs. We are the choice of hundreds of customers around the city 
                                    and around the state - let us be your choice. LET US show you why, 
                                    "You Can Count Us - We're Texans Serving Texans 24 Hours a Day!!".</p>  
                            </td>
                        </tr>
                        <tr>
                            <td style="height:100%">
                                <h3>We are Serving following Areas</h3>
                            </td>
                        </tr>
                        <tr>
                            <td>
                                <div id="contactDetails"></div>
                            </td> 
                        </tr>
                    </table>
                    </td>
                    </tr>             
                </table>
                </td>
            </tr>             
        </table>
    </form>
</body>
</html>
