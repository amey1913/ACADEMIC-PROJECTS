<%@ Page Language="C#" AutoEventWireup="true" CodeFile="ContactUS.aspx.cs" Inherits="_Default" %>
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
                    <table style="width:100%; height:100%; border:groove" border ="1" class="contactUS">
                        <tr>
                            <td colspan="2" >
                            <h1>Please Email US All Your Concerns!</h1>
                            <table class="emailUS" style="width:90%; height:60%;">
                            <tr>
                                <td>
                                    <asp:Label id="emailLabel" Text = "Enter Your Email Address:" runat="server" Font-Bold =" true" ForeColor="Brown"  Width="100%" ></asp:Label>
                                </td>
                                <td>
                                        <asp:TextBox id="emailText" runat="server" Font-Size="24" Width="100%" ></asp:TextBox>
                                        <asp:RequiredFieldValidator id="validEmailReq" runat="server" 
                                                            ErrorMessage="Required!" 
                                                            ControlToValidate="emailText"  
                                                            ForeColor="Red"
                                                            ValidationGroup="emailMsgGroup"
                                                            Display ="Dynamic"/>
                                        <asp:RegularExpressionValidator ID="validEmailReg" runat="server"     
                                                ErrorMessage="Please Enter Valid Email-Id. Eg. example@exmaple.com" 
                                                ControlToValidate="emailText"     
                                                ValidationExpression="^([\w\.\-]+)@([\w\-]+)((\.(\w){2,3})+)$"
                                                ForeColor="Red"
                                                ValidationGroup="emailMsgGroup"
                                                Display ="Dynamic" />
                                    </td>
                                </tr>
                                <tr>
                                    <td colspan ="2">
                                    <asp:TextBox id="messageText" TextMode ="MultiLine" runat="server" Height="220px" Font-Size="24" Width="100%" Text="Type your message here." />
                                        <asp:RequiredFieldValidator id="validMsgreq" runat="server" 
                                                                        ErrorMessage="Message is Required." 
                                                                        ControlToValidate="messageText"  
                                                                        ForeColor="Red"
                                                                        ValidationGroup="emailMsgGroup"
                                                                        Display ="Dynamic"/>
                                    </td>
                                </tr>
                                <tr>
                                    <td colspan ="2">
                                        <asp:Button id="submitReq" Text="Submit" runat="server" OnClick="submitMesage" Width="40%" Height="100%" Font-Size ="24px" ForeColor="Brown" Font-Bold="true"></asp:Button>
                                    </td>
                                </tr> 
                                </table>
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
        </table>
    </form>
</body>
</html>
