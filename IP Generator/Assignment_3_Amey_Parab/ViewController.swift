//
//  ViewController.swift
//  Assignment_3_Amey_Parab
//
//  Created by Parab, Amey on 3/29/16.
//  Copyright © 2016 Parab, Amey. All rights reserved.
//

import UIKit

class ViewController: UIViewController, UITableViewDelegate, UITableViewDataSource{

    var addressLis:[String] = []
    
    @IBOutlet weak var ip: UITextField!
    
    @IBOutlet weak var mask: UITextField!
    
    @IBOutlet weak var table: UITableView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        
        table.hidden = true
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
        self.table.delegate = self
        self.table.dataSource = self
    }
    
    @IBAction func generateIPRange(sender: UIButton)
    {
        table.hidden = false
        let obj = IPGen(ip: "192.168.1.0", subnetBits: 26)
        addressLis = obj.rangeOfIps()
        self.table.reloadData()
    }
    
    func numberOfSectionsInTableView(tableView: UITableView) -> Int {
        return 1
    }
    
    func tableView(tableView: UITableView, titleForHeaderInSection section: Int) -> String? {
        return "Valid IP Addresses:"
    }
    
    func tableView(tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return 100
    }
    
    func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell {
        let contactIdentifier = "IP"
        let cell = tableView.dequeueReusableCellWithIdentifier(contactIdentifier, forIndexPath: indexPath)
        let ipAddress = addressLis[indexPath.row]
        print(indexPath.row)
        print(ipAddress)
        cell.textLabel!.text = ipAddress
        return cell
    }
}

