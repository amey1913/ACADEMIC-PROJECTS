<%@ Page Language="C#" AutoEventWireup="true" CodeFile="Accounts.aspx.cs" Inherits="_Default" %>
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
                <td style="width:25%; height:100%">
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
                <td class="Login_Accounts" style="width:75%; height:100%">
                    <asp:Panel id = "login_users" runat="server">
                        <asp:RadioButtonList ID="New_Current_Users" runat="server" AutoPostBack="True" onselectedindexchanged="accountIndexChanged"
                            RepeatDirection="Horizontal" Height="100%" Width="100%" CssClass="radios">
                            <asp:ListItem Text="I have an existing account" Value="current_users" Selected="True"></asp:ListItem>
                            <asp:ListItem Text="I do not have an existing account" Value="new_users" Selected="False"></asp:ListItem>
                        </asp:RadioButtonList>
                        <br />
                    </asp:Panel>

                    <asp:Panel id = "current_users_panel" runat="server">
                        <fieldset>
                            <legend>Existing Account</legend>
                              <table>
                                <tr>
                                    <td style="width:30%; height:100%; border:none">
                                        <asp:Label id="email_L" Text = "Email Address:" runat="server" ></asp:Label>
                                        <asp:Label id="Label9" Text = "*" runat="server" ForeColor="Red" ></asp:Label>
                                    </td>
                                    <td style="width:70%; height:100%; border:none ; padding:0 0 0 50px">
                                        <asp:TextBox id="email_T" Width ="70%" runat="server" 
                                            Height="100%"  Font-Size="X-Large" ValidationGroup="G1"></asp:TextBox>         
                                        
                                        <asp:RequiredFieldValidator ID="RequiredFieldValidator1" 
                                                                       
                                                                    runat="server" 
                                                                    ControlToValidate="email_T" 
                                                                    ErrorMessage="Required"
                                                                    ForeColor="Red"
                                                                    Display="Dynamic"
                                                                    ValidationGroup="G1" />
                                        
                                        <asp:RegularExpressionValidator ID="RegularExpressionValidator1" runat="server"     
                                                    
                                                ErrorMessage="Invalid Email-ID!" 
                                                ControlToValidate="email_T"     
                                                ValidationExpression="^([\w\.\-]+)@([\w\-]+)((\.(\w){2,3})+)$"
                                                ForeColor="Red"
                                                Display="Dynamic" 
                                                ValidationGroup="G1"/>
                                    </td>
                                </tr>
                                <tr>
                                    <td style="width:30%; height:100%; border:none">
                                        <asp:Label id="password_L" Text = "Access Code:"  runat="server" ></asp:Label>
                                        <asp:Label id="Label10" Text = "*" runat="server" ForeColor="Red" ></asp:Label>
                   
                                    </td>
                                    <td  style="width:70%; height:100%; border:none; padding:10px 0 20px 50px"> 
                                        <asp:TextBox id="password_T" Width ="70%" TextMode ="Password" runat="server" Height="100%"
                                              Font-Size="X-Large" ValidationGroup="G1"></asp:TextBox>
                                        
                                        <asp:RequiredFieldValidator ID="RequiredFieldValidator2" 
                                                                    ValidationGroup="G1"   
                                                                    runat="server" 
                                                                    ControlToValidate="password_T" 
                                                                    ErrorMessage="Required"
                                                                    ForeColor="Red" 
                                                                    Display="Dynamic"/>

                                        <asp:RegularExpressionValidator ID="RegularExpressionValidator2" runat="server"     
                                                        ValidationGroup="G1"
                                                        ErrorMessage="Must be 6 Digits!" 
                                                        ControlToValidate="password_T"     
                                                        ValidationExpression="^[0-9]{6}$"
                                                        ForeColor="Red"
                                                        Display="Dynamic" />
                                    </td>
                                </tr>
                                <tr>
                                    <td  style="width:30%; height:100%; border:none" >
                                        <asp:LinkButton ID="Forgot_Password" OnClick="reover_link_Click" Text ="Forgot My Access Code" runat="server" ></asp:LinkButton>
                                    </td>
                                    <td  style="width:70%; height:100%; border:none; padding:20px 20px 20px 50px">
                                        <asp:Button id="login_B" Text="Log In" runat="server" OnClick="login_B_Click" Font-Size="X-Large" Height="40px" Width="200px"></asp:Button>
                                    </td>
                                </tr>
                            </table>                       
                        </fieldset>
                    </asp:Panel>

                    <asp:Panel id = "new_users_panel" Visible =" False" runat="server">
                        <fieldset>

                            <legend>Create New Account</legend>
                            <table style="width:100%; height:100%; border:none">
                                <tr>
                                    <td colspan="2" style="width:100%; height:100%; border:none">
                                    <asp:Label id="line1_L" Text = "Apply Online to open a New Account with us." runat="server" ></asp:Label>
                                    <br />
                                    <asp:Label id="line2_L" Text = "To complete an online application, please fill out the following information and then hit the 'Create Account' button." runat="server" ></asp:Label>
                                    </td>
                                </tr>
                                <tr>
                                    <td style="width:30%; height:100%; border:none">
                                        <asp:Label id="name_L" Text = "Full Name" runat="server" ></asp:Label>
                                        <asp:Label id="astr1" Text = "*" runat="server" ForeColor="Red" ></asp:Label>
                                    </td>
                                    <td style="width:70%; height:100%; border:none; padding:10px 10px 10px 10px">
                                        <asp:TextBox id="name_T" Width ="80%" runat="server" Height="100%" 
                                            Font-Size="X-Large" ></asp:TextBox>
                                        <asp:RequiredFieldValidator ID="RequiredFieldValidator4" 
                                                                    runat="server" 
                                                                    ControlToValidate="name_T" 
                                                                    ForeColor="Red"
                                                                    ErrorMessage ="Required"
                                            Display="Dynamic"></asp:RequiredFieldValidator>
                                    </td>
                                </tr>
                                <tr>
                                    <td style="width:30%; height:100%; border:none">
                                        <asp:Label id="company_L" Text = "Company" runat="server" ></asp:Label>
                                    </td>
                                    <td style="width:70%; height:100%; border:none; padding:10px 10px 10px 10px">
                                        <asp:TextBox id="company_T" Width ="80%" runat="server" Height="100%" Font-Size="X-Large" ></asp:TextBox>
                                    </td>
                                </tr>
                                <tr>
                                    <td style="width:30%; height:100%; border:none">
                                        <asp:Label id="addr_L" Text = "Mailing Address" runat="server" ></asp:Label>
                                        <asp:Label id="Label1" Text = "*" runat="server" ForeColor="Red" ></asp:Label>
                                    </td>
                                    <td style="width:70%; height:100%; border:none; padding:10px 10px 10px 10px">
                                        <asp:TextBox id="addr_T" Width ="80%" runat="server" Height="100%" 
                                             Font-Size="X-Large" ></asp:TextBox>
                                        <asp:RequiredFieldValidator ID="RequiredFieldValidator5" 
                                                                       
                                                                    runat="server" 
                                                                    ControlToValidate="addr_T" 
                                                                    ForeColor="Red"
                                            Display="Dynamic">Required</asp:RequiredFieldValidator>
                                    </td>
                                </tr>
                                <tr>
                                <td style="width:30%; height:100%; border:none">
                                    <asp:Label id="phone_L" Text = "Phone Number" runat="server" ></asp:Label>
                                    <asp:Label id="Label2" Text = "*" runat="server" ForeColor="Red" ></asp:Label>
                                </td>
                                <td style="width:70%; height:100%; border:none; padding:10px 10px 10px 10px">
                                    <asp:TextBox id="phone_T" Width ="80%" runat="server" Height="100%"
                                         Font-Size="X-Large" ></asp:TextBox>
                                    
                                    <asp:RequiredFieldValidator ID="RequiredFieldValidator6" 
                                                                       
                                                                    runat="server" 
                                                                    ControlToValidate="phone_T" 
                                                                    ErrorMessage="Required"
                                                                    ForeColor="Red"
                                        Display="Dynamic" />

                                    <asp:RegularExpressionValidator ID="RegularExpressionValidator4" runat="server"     
                                                    
                                                ErrorMessage="Invalid Phone Number!" 
                                                ControlToValidate="phone_T"     
                                                ValidationExpression="^[0-9]{3}-[0-9]{3}-[0-9]{4}$"
                                                ForeColor="Red" 
                                        Display="Dynamic"/>
                                </td>
                            </tr>
                            <tr>
                                <td style="width:30%; height:100%; border:none">
                                    <asp:Label id="email_id_L" Text = "Email Address" runat="server" ></asp:Label>
                                    <asp:Label id="Label3" Text = "*" runat="server" ForeColor="Red" ></asp:Label>
                                </td>
                                <td style="width:70%; height:100%; border:none; padding:10px 10px 10px 10px">
                                    <asp:TextBox id="email_id_T" Width ="80%" runat="server" Height="100%" 
                                         Font-Size="X-Large" ></asp:TextBox>

                                    <asp:RequiredFieldValidator ID="RequiredFieldValidator7" 
                                                                       
                                                                    runat="server" 
                                                                    ControlToValidate="email_id_T" 
                                                                    ErrorMessage="Required"
                                                                    ForeColor="Red" 
                                        Display="Dynamic"/>

                                    <asp:RegularExpressionValidator ID="RegularExpressionValidator5" runat="server"     
                                                    
                                                ErrorMessage="Invalid Email ID!" 
                                                ControlToValidate="email_id_T"     
                                                ValidationExpression="^([\w\.\-]+)@([\w\-]+)((\.(\w){2,3})+)$"
                                                ForeColor="Red" 
                                        Display="Dynamic"/>
                                </td>
                            </tr>
                            <tr>
                                <td style="width:30%; height:100%; border:none">
                                    <asp:Label id="acc_code_L" Text = "Access Code" runat="server" ></asp:Label>
                                </td>
                                <td style="width:70%; height:100%; border:none; padding:10px 10px 10px 10px">
                                    <asp:TextBox id="acc_code_T" BackColor="Violet" ForeColor="WhiteSmoke" Width ="80%" ReadOnly="true" runat="server" OnLoad ="getAccessCode" Height="100%" Font-Size="X-Large"></asp:TextBox>
                                </td>
                            </tr>
                            <tr>
                                <td style="width:30%; height:100%; border:none">
                                    <asp:Label id="code_L" Text = "Enter Access Code" runat="server" ></asp:Label>
                                    <asp:Label id="Label4" Text = "*" runat="server" ForeColor="Red" ></asp:Label>
                                </td>
                                <td style="width:70%; height:100%; border:none; padding:10px 10px 10px 10px">
                                    <asp:TextBox id="code_T" Width ="80%" runat="server" Height="100%"  Font-Size="X-Large" ></asp:TextBox>

                                    <asp:RequiredFieldValidator ID="RequiredFieldValidator8" 
                                                                       
                                                                    runat="server" 
                                                                    ControlToValidate="code_T" 
                                                                    ForeColor="Red"
                                        Display="Dynamic">Required</asp:RequiredFieldValidator>
                                    <asp:CompareValidator id="newTextComp7" runat="server" 
                                                            ControlToCompare="acc_code_T" 
                                                            ControlToValidate="code_T" 
                                                            ForeColor="Red"
                                        Display="Dynamic">Your Access Code does not match.</asp:CompareValidator>
                                                            
                                </td>
                            </tr>
                            <tr>
                                <td style="width:30%; height:100%; border:none">                       
                                    &nbsp
                                </td>
                                <td style="width:70%; height:100%; border:none; padding:10px 10px 10px 10px">         
                                    <asp:Button id="create_account_L" Text="Create Account" runat="server" Height="100%" Width="40%" Font-Size="X-Large" Font-Underline="False" OnClick="create_account_L_Click" ></asp:Button>
                                    <asp:Button id="no_thanks_L" Text="Back To Accounts" runat="server" Height="100%" Width="40%" Font-Size="X-Large" OnClick="no_thanks_L_Click" ValidationGroup="G2" ></asp:Button>
                                </td>
                            </tr>
                        </table>
                        </fieldset>
                    </asp:Panel>

                    <asp:Panel id = "recover_password" runat="server">
                        <fieldset>
                            <legend>Recover Password</legend>
                              <table>
                                <tr>
                                    <td style="width:30%; height:100%; border:none; padding:20px 20px 20px 50px ">
                                        <asp:Label id="Label11" Text = "Email Address:" runat="server" ></asp:Label>
                                    </td>
                                    <td style="width:100%; height:100%; border:none; padding:20px 20px 20px 50px ">
                                        <asp:TextBox id="email_T2" Width ="100%" runat="server" 
                                            Height="100%"  Font-Size="X-Large"
                                            AutoPostBack="true" OnTextChanged="recover_button_click"></asp:TextBox>
                                        <asp:RegularExpressionValidator ID="RegularExpressionValidator3" runat="server"     
                                                                        ErrorMessage="Invalid Email-ID!" 
                                                                        ControlToValidate="email_T2"     
                                                                        ValidationExpression="^([\w\.\-]+)@([\w\-]+)((\.(\w){2,3})+)$"
                                                                        ForeColor="Red"
                                                                        Display="Dynamic" /> 
                                        <asp:RequiredFieldValidator ID="RequiredFieldValidator3" 
                                                                    runat="server" 
                                                                    ControlToValidate="email_T2" 
                                                                    ForeColor="Red"
                                                                    Display="Dynamic">Required</asp:RequiredFieldValidator>
                                    </td>
                                    <td  style="width:20%; height:100%; border:none; padding:20px 20px 20px 50px">
                                        <asp:Button id="reoverPassword" OnClick="recover_button_click" Text="Recover Password" runat="server" Font-Size="X-Large" Height="40px" Width="100%"></asp:Button>
                                    </td>
                                </tr>                                    
                                <tr>
                                    <td  style="width:50%; height:100%; border:none; padding:20px 20px 20px 50px" >
                                        <asp:HyperLink ID="goBackAccount" NavigateUrl="~/Accounts.aspx" Text="Go Back To Account Page" runat="server" ></asp:HyperLink>
                                    </td>
                                </tr>
                            </table>                       
                        </fieldset>
                    </asp:Panel>

                    <asp:Panel id = "user_account_panel" Visible = "False" runat = "server">
                        <table style="width:100%; height:100%; border:none">
                            <tr>    
                                <td style="width:70%; height:100%; border:none;text-align:left">    
                                     <asp:Label id="login_L1" Text = "" OnLoad="update_Welcome_lable" runat="server" ></asp:Label> 
                                </td>
                                <td style="width:30%; height:100%; border:none;text-align:right">
                                     <asp:LinkButton ID="log_out" Text="Log Out" runat="server" OnClick="log_out_Click" ValidationGroup="G5"></asp:LinkButton>
                                </td>
                            </tr>
                        </table>
                        <br />
                        <br />
                        <fieldset>
                        <legend>New Delivery Request</legend>
                            <table style="width:100%; height:100%; border:none">
                                <tr>
                                    <td colspan="2" style="width:100%; height:100%; border:none; text-align:center; color:#b12626; font-size:40px; padding:50px 10px 50px 10px">
                                        <asp:Label id="loginL2" Text = "Please enter Delivery Details below" runat="server" ></asp:Label>
                                        <br />
                                    </td>
                                </tr>
                                <tr>
                                    <td style="width:30%; height:100%; border:none">
                                        <asp:Label id="log3nL2" Text = "Pickup Address" runat="server" ></asp:Label>
                                        <asp:Label id="Label6" Text = "*" runat="server" ForeColor="Red" ></asp:Label>
                                    </td>
                                    <td style="width:70%; height:100%; border:none; padding:10px 10px 10px 10px">  
                                        <asp:TextBox id="loginT1" Width ="80%" runat="server" Font-Size="X-Large" Height="100%" ></asp:TextBox>
                                        <asp:RequiredFieldValidator ID="RequiredFieldValidator11" 
                                                                       
                                                                    runat="server" 
                                                                    ControlToValidate="loginT1" 
                                                                    ForeColor="Red"
                                            Display="Dynamic">Required</asp:RequiredFieldValidator>
                                    </td>
                                </tr>
                                <tr>
                                    <td style="width:30%; height:100%; border:none">
                                        <asp:Label id="loginL4" Text = "Recipient Address" runat="server" ></asp:Label>
                                        <asp:Label id="Label7" Text = "*" runat="server" ForeColor="Red" ></asp:Label>
                                    </td>
                                    <td style="width:70%; height:100%; border:none; padding:10px 10px 10px 10px">
                                        <asp:TextBox id="loginT2" Width ="80%" runat="server" Font-Size="X-Large" Height="100%" ></asp:TextBox>
                                        <asp:RequiredFieldValidator ID="RequiredFieldValidator10" 
                                                                       
                                                                    runat="server" 
                                                                    ControlToValidate="loginT2" 
                                                                    ForeColor="Red"
                                            Display="Dynamic">Required</asp:RequiredFieldValidator>
                                        <br />
                                    </td>
                                </tr>
                                <tr>
                                    <td style="width:30%; height:100%; border:none">
                                        <asp:Label id="loginL5" Text = "Recipient Phone" runat="server" ></asp:Label>
                                        <asp:Label id="Label5" Text = "*" runat="server" ForeColor="Red" ></asp:Label>
                                    </td>
                                    <td style="width:70%; height:100%; border:none; padding:10px 10px 10px 10px">
                                        <asp:TextBox id="loginT3" Width ="80%" runat="server" Font-Size="X-Large" Height="100%" ></asp:TextBox>
                                        <asp:RequiredFieldValidator ID="RequiredFieldValidator9" 
                                                                       
                                                                    runat="server" 
                                                                    ControlToValidate="loginT3" 
                                                                    ForeColor="Red"
                                            Display="Dynamic">Required</asp:RequiredFieldValidator>

                                        <asp:RegularExpressionValidator ID="RegularExpressionValidator6" runat="server"     
                                                    
                                                ErrorMessage="Invalid Phone Number!" 
                                                ControlToValidate="loginT3"     
                                                ValidationExpression="^[0-9]{3}-[0-9]{3}-[0-9]{4}$"
                                                ForeColor="Red" 
                                            Display="Dynamic"/>
                                        <br />
                                    </td>
                                </tr>
                                <tr>
                                    <td style="width:30%; height:100%; border:none">
                                        <asp:Label id="loginL6" Text = "Provide a Description (List Items to Deliver)" runat="server" ></asp:Label>
                                        <asp:Label id="Label8" Text = "*" runat="server" ForeColor="Red" ></asp:Label>
                                    </td>
                                    <td style="width:70%; height:100%; border:none; padding:10px 10px 10px 10px">
                                        <asp:TextBox id="loginT4" TextMode ="MultiLine" Width= "80%" runat="server" Font-Size="X-Large" Height="100%" Rows="5" ></asp:TextBox>
                                        <asp:RequiredFieldValidator ID="RequiredFieldValidator12" 
                                                                       
                                                                    runat="server" 
                                                                    ControlToValidate="loginT4" 
                                                                    ForeColor="Red"
                                            Display="Dynamic">Required</asp:RequiredFieldValidator>
                                    <br />
                                    </td>
                                </tr>
                                <tr>
                                    <td style="width:30%; height:100%; border:none">                       
                                        &nbsp
                                    </td>
                                    <td style="width:70%; height:100%; border:none; padding:10px 10px 10px 10px">         
                                        <asp:Button id="submitReq" Text="Submit Request" runat="server" Font-Size="X-Large" Height="100%" Width="40%" OnClick="submitReq_Click"></asp:Button>
                                    </td>
                                </tr>
                        </table>
                        </fieldset>
                    </asp:Panel>
                 </td>   
            </tr>             
        </table>
    </form>
</body>
</html>
