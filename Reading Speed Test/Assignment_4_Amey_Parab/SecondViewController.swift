//
//  SecondViewController.swift
//  Assignment_4_Amey_Parab
//
//  Created by Parab, Amey on 4/20/16.
//  Copyright © 2016 Parab, Amey. All rights reserved.
//

import UIKit
import CoreData

class SecondViewController: UIViewController , UITableViewDataSource, UITableViewDelegate{

    var UserList:[AnyObject] = []
    var threeAttempts:[AnyObject] = []
    var totCounts:[AnyObject] = []
    
    var user: String = "" // Current User
    
    @IBOutlet weak var tableView: UITableView!
    
    @IBOutlet weak var l1: UILabel!
    @IBOutlet weak var l2: UILabel!
    @IBOutlet weak var l3: UILabel!
    @IBOutlet weak var totl: UILabel!
    
    @IBOutlet weak var stat_L: UILabel!
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
               self.tableView.delegate = self
        self.tableView.dataSource = self
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    override func viewWillAppear(animated: Bool) {
        
        let defaults = NSUserDefaults.standardUserDefaults()
        if (defaults.stringForKey("currentUser") != nil){
            user = defaults.stringForKey("currentUser")!
            fetchData()
            fetchData2()
            fetchData3()
            tableView.reloadData()
            
        }else{
            user = ""
        }
    
    }
    
    func fetchData3()
    {
        let appDelegate = UIApplication.sharedApplication().delegate as! AppDelegate
        let context =  appDelegate.managedObjectContext
        
        let fetch = NSFetchRequest(entityName: "Users")
        let predicate = NSPredicate(format: "userName = %@ ", user)
        fetch.predicate = predicate
        fetch.resultType = .DictionaryResultType
        let sumExpression = NSExpression(format: "count:(speed)")
        let sumED = NSExpressionDescription()
        sumED.expression = sumExpression
        sumED.name = "Counts"
        sumED.expressionResultType = .Integer32AttributeType
        
        fetch.propertiesToFetch = ["userName", sumED]
        fetch.propertiesToGroupBy = ["userName"]
        let sort = NSSortDescriptor(key: "userName", ascending: false)
        
        fetch.sortDescriptors = [sort]
        
        do {
            totCounts = try context.executeFetchRequest(fetch)
            
        } catch {
            let fetchError = error as NSError
            print(fetchError)
        }
        
        if totCounts.count >= 1
        {
            totl.text = totCounts[0].valueForKey("Counts")!.description
        }else
        {
            totl.text = "0"
        }
        
    }

    func fetchData2()
    {
        let appDelegate = UIApplication.sharedApplication().delegate as! AppDelegate
        let context =  appDelegate.managedObjectContext
        
        let fetch = NSFetchRequest(entityName: "Users")
        let predicate = NSPredicate(format: "userName = %@ ", user)
        fetch.predicate = predicate
        fetch.resultType = .DictionaryResultType
        
        fetch.propertiesToFetch = ["userName", "speed"]
        let sort = NSSortDescriptor(key: "timeStamp", ascending: false)
        
        fetch.fetchLimit = 3
        fetch.sortDescriptors = [sort]
        
        threeAttempts = try! context.executeFetchRequest(fetch)
        print("reached 2")

        upadteThreeAttempts()
        print("reached 22")

    }
    
    func upadteThreeAttempts()
    {
        if threeAttempts.count == 1{
            l1.text = threeAttempts[0].valueForKey("speed")!.description
            l2.text = "0"
            l3.text = "0"
        }else if threeAttempts.count == 2{
            l1.text = threeAttempts[0].valueForKey("speed")!.description
            l2.text = threeAttempts[1].valueForKey("speed")!.description
            l3.text = "0"
        }else if threeAttempts.count == 3{
            l1.text = threeAttempts[0].valueForKey("speed")!.description
            l2.text = threeAttempts[1].valueForKey("speed")!.description
            l3.text = threeAttempts[2].valueForKey("speed")!.description
        }else{
            l1.text = "0"
            l2.text = "0"
            l3.text = "0"
        }

    }
    
    func fetchData()
    {
        let appDelegate = UIApplication.sharedApplication().delegate as! AppDelegate
        let context =  appDelegate.managedObjectContext
        
        let fetch = NSFetchRequest(entityName: "Users")
        fetch.resultType = .DictionaryResultType
        let sumExpression = NSExpression(format: "max:(speed)")
        let sumED = NSExpressionDescription()
        sumED.expression = sumExpression
        sumED.name = "TopSpeed"
        sumED.expressionResultType = .Integer32AttributeType
        
        fetch.propertiesToFetch = ["userName", sumED]
        fetch.propertiesToGroupBy = ["userName"]
        let sort = NSSortDescriptor(key: "speed", ascending: false)
        
        fetch.sortDescriptors = [sort]
       
        do {
            UserList = try context.executeFetchRequest(fetch)
            
        } catch {
            let fetchError = error as NSError
            print(fetchError)
        }
        
        self.tableView.reloadData() // Reload table data
    }
    
    func numberOfSectionsInTableView(tableView: UITableView) -> Int {
        return 1
    }
    
    func tableView(tableView: UITableView, titleForHeaderInSection section: Int) -> String? {
        return "Top Scorers :"
    }
    
    func tableView(tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return UserList.count
    }
    
    func tableView(tableView: UITableView, cellForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell {
        let contactIdentifier = "User"
        let cell = tableView.dequeueReusableCellWithIdentifier(contactIdentifier, forIndexPath: indexPath)
        let object = UserList[indexPath.row]
        print(indexPath.row)
        cell.textLabel!.text = object.valueForKey("userName")!.description
        cell.detailTextLabel!.text = "Top Speed: " + object.valueForKey("TopSpeed")!.description

        return cell
    }
}

