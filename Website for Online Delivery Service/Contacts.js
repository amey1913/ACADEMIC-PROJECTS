function loadDoc()
{
        var xmlRequest = new XMLHttpRequest();
        xmlRequest.open("GET", "contactinfo.xml", true);
        xmlRequest.send(null);
        xmlRequest.onreadystatechange = function () {  if (xmlRequest.readyState == 4 && xmlRequest.status == 200) 
                                                        {setContacts(xmlRequest);} 
                                                    };
}

function setContacts(xmlRequest) {
    var xmlFile = xmlRequest.responseXML;
    rootNode = xmlFile.documentElement;
    var nextnode = rootNode.getElementsByTagName("info");

    var Adv1 = "";
    Adv1 += "<h1>Contact Us</h1>" +
            "<strong>Texans serving Texans<br/>" +
            "24 Hours a Day!</strong> " +
            "<h1>Toll Free</h1>" +
            "<strong><u>" + nextnode[0].getAttribute("toll-free-phone") + "</u></strong>" +
            "<h1>Houston</h1>" +
            "<strong><u>" + nextnode[0].getAttribute("houston-phone") + "</u></strong>" +
            "<h1>E-mail</h1>" +
            "<strong>" + nextnode[0].getAttribute("contact-email") + "</strong> ";

            document.getElementById("phoneDetails").innerHTML = Adv1;

    if (document.getElementById("contactDetails")) {
        var contacts = "";
        contacts += "<table class =\"Contact_Text\"><tr><td>" + nextnode[0].getAttribute("city-one") +
                "</td><td>" + nextnode[0].getAttribute("city-two") +
                "</td><td>" + nextnode[0].getAttribute("city-three") +"</td></tr>" +
                "<tr><td><u>" + nextnode[0].getAttribute("houston-phone") + "</u></td>" +
                "<td><u>" + nextnode[0].getAttribute("austin-phone") + "</u></td>" +
                "<td><u>" + nextnode[0].getAttribute("dallas-phone") + "</u></td></tr>" +
                "<tr><td>" + nextnode[0].getAttribute("city-four") +
                "</td><td>" + nextnode[0].getAttribute("city-five") +
                "</td><td>" + nextnode[0].getAttribute("city-six") + "</td></tr>" +
                "<tr><td><u>" + nextnode[0].getAttribute("elpaso-phone") + "</u></td>" +
                "<td><u>" + nextnode[0].getAttribute("sanantonio-phone") + "</u></td>" +
                "<td><u>" + nextnode[0].getAttribute("riogrande-phone") + "</u></td></tr>" +
                "<tr><td>" + nextnode[0].getAttribute("city-seven") +
                "</td><td>" + nextnode[0].getAttribute("city-eight") +
                "</td><td>"  + nextnode[0].getAttribute("city-nine") + "</td></tr>" +
                "<tr><td><u>" + nextnode[0].getAttribute("corpus-phone") + "</u></td>" + 
                "<td><u>" + nextnode[0].getAttribute("easttx-phone") + "</u></td>" +
                "<td><u>" + nextnode[0].getAttribute("westtx-phone") + "</u></td></tr></table>";

        document.getElementById("contactDetails").innerHTML = contacts;
    } 
}