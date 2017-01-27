<%@ Page Language="C#" AutoEventWireup="true" CodeFile="Default.aspx.cs" Inherits="_Default" %>
<!DOCTYPE html>

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>T & P Services</title>
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
                    <table style="width:100%; height:100%; border:groove" border ="1" class="Content_Text">
                        <tr>
                            <td colspan="2" >
                               <h1>The Service You can Trust</h1>
                                    <p> Enjoy a 1-to-1 relationship without your very own T & P delivery Service, who delivers for you each time
                                       and learns your preferences.</p>
                                    <p> Get your favourite products from store of your preference and get delivered 
                                       right to your door. </p>
                                    <p> We offer a range of other services including Medical deliveries Legal courier deliveries etc. </p>
                                    
                                    <p> It's all backed by our 100% Stress-Free Guarantee.</p>
                             </td>   
                        </tr>
                        <tr>
                            <td style="background-color:#ffffff; background-image:url('Images/img_1.png'); background-size: 100% 110%;">
                            </td>
                            <td style="background-color:#ffffff; background-image:url('Images/img_2.png'); background-size: 100% 110%;">
                            </td>
                        </tr>
                    </table>
                </td>
            </tr>  
            <tr>
                <td colspan="2" style="width:100%">
                    <table>
                        <tr>
                            <td style="Width:25%; Height:280px">
                                <asp:AdRotator id="ads1" runat="server" AdvertisementFile="ad.xml" Target="_blank" KeywordFilter="delv1"  Width ="100%" Height="100%"/>
                            </td>
                            <td style="Width:25%; Height:280px">
                                <asp:AdRotator id="ads2" runat="server" AdvertisementFile="ad.xml" Target="_blank" KeywordFilter="delv2" Width ="100%" Height="100%"/>
                            </td>
                            <td style="Width:25%; Height:280px">
                                <asp:AdRotator id="ads3" runat="server" AdvertisementFile="ad.xml" Target="_blank" KeywordFilter="delv1"  Width ="100%" Height="100%"/>
                            </td>
                            <td style="Width:25%; Height:280px">
                                <asp:AdRotator id="ads4" runat="server" AdvertisementFile="ad.xml" Target="_blank" KeywordFilter="delv2"  Width ="100%" Height="100%"/>
                            </td>
                        </tr>
                    </table>
                </td>
            </tr>           
        </table>
    </form>
</body>
</html>
