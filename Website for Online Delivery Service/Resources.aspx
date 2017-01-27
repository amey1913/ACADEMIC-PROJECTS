<%@ Page Language="C#" AutoEventWireup="true" CodeFile="Resources.aspx.cs" Inherits="_Default" %>
<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Resources</title>
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
                    <table style="width:100%; height:100%" class="Resources_Text">
                       <tr>
                            <td colspan = "2">                                
                                <h1>Resources Links</h1>                                
                                <p>Click Below to Access The Forms</p>  
                            </td>
                        </tr>
                        <tr>
                            <td>
                                <a href="Files/expressbill.pdf" target="_blank"><img src ="Images/pdf-icon.png"/>
                                <p>Express Bill</p></a>
                            </td>
                            <td>
                                <a href="Files/CardAthorizationform.pdf" target="_blank"><img src ="Images/pdf-icon.png"/>
                                <p>Card Authorization Form</p></a>
                           </td> 
                        </tr>
                    </table>
                </td>
            </tr>             
        </table>
    </form>
</body>
</html>
