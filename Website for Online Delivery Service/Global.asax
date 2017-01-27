<%@ Application Language="C#" %>
<%@ Import Namespace="System.Data.SqlClient" %>
<%@ Import Namespace="System.Data" %> 

<script runat="server">

    void Application_Start(object sender, EventArgs e) 
    {
        // Code that runs on application startup
        Application["AllUsersList"] = new List<User>();
        Application["AllUsersList"] = null;
        List<User> allUsersList = new List<User>();
        String connStr = ConfigurationManager.ConnectionStrings["connectionString"].ConnectionString;
        using (SqlConnection conn = new SqlConnection(connStr))
        {
            string sql = "SELECT * from ParabA2_WADsp16_users";
            using (SqlCommand command = new SqlCommand(sql, conn))
            {
                try
                {   
                    conn.Open();
                    SqlDataReader sqlReader = command.ExecuteReader();
                    
                    while (sqlReader.Read())
                    {
                        User tempUser = new User();
                        tempUser.FullName = (String)sqlReader["fullName"];
                        tempUser.Company = (String)sqlReader["company"];
                        tempUser.MailingAddress = (String)sqlReader["mailingAddress"];
                        tempUser.PhoneNumber = (String)sqlReader["phoneNumber"];
                        tempUser.EmailAddress = (String)sqlReader["emailAddress"];
                        tempUser.AccessCode = (int)sqlReader["accessCode"];
                        using (SqlConnection conn1 = new SqlConnection(connStr))
                        {
                            string sql1 = "SELECT * from ParabA2_WADsp16_delivery_request where accessCode = " + tempUser.AccessCode;
                            using (SqlCommand command1 = new SqlCommand(sql1, conn1))
                            {
                                try
                                {
                                    conn1.Open();
                                    SqlDataReader sqlReader1 = command1.ExecuteReader();
                                    while (sqlReader1.Read())
                                    {
                                        DeliveryDetail tempDel = new DeliveryDetail();
                                        tempDel.RequestDate = (DateTime)sqlReader1["requestDate"];
                                        tempDel.PickupAddress = (String)sqlReader1["pickupAddress"];
                                        tempDel.ReceipientAddress = (String)sqlReader1["receipientAddress"];
                                        tempDel.ReceipientPhone = (String)sqlReader1["receipientPhone"];
                                        tempDel.Description = (String)sqlReader1["description"];
                                        tempUser.DeliveryDetailsList.Add(tempDel);
                                    }

                                }
                                catch
                                {

                                }
                                finally
                                {
                                    conn1.Close();
                                }
                                allUsersList.Add(tempUser);
                                

                            }
                        }
                    }
                    
                }
                finally
                {
                    conn.Close();
                    Application["AllUsersList"] = allUsersList;
                }
                
            }
            
        }
        

    }
    
    void Application_End(object sender, EventArgs e) 
    {
        //  Code that runs on application shutdown

    }
        
    void Application_Error(object sender, EventArgs e) 
    { 
        // Code that runs when an unhandled error occurs

    }

    void Session_Start(object sender, EventArgs e) 
    {
        // Code that runs when a new session is started

    }

    void Session_End(object sender, EventArgs e) 
    {
        // Code that runs when a session ends. 
        // Note: The Session_End event is raised only when the sessionstate mode
        // is set to InProc in the Web.config file. If session mode is set to StateServer 
        // or SQLServer, the event is not raised.

    }
       
</script>
