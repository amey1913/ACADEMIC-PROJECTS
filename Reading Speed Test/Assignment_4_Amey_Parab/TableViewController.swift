//
//  TableViewController.swift
//  Assignment_4_Amey_Parab
//
//  Created by Parab, Amey on 4/20/16.
//  Copyright © 2016 Parab, Amey. All rights reserved.
//

import UIKit
import CoreData

class TableViewController: UIViewController , UITableViewDataSource, UITableViewDelegate, UITextFieldDelegate{

    var UserList:[AnyObject] = []
    var selectedUser:String = ""
    
    var ind : NSIndexPath!
    
    @IBOutlet weak var user_T: UITextField!
    @IBOutlet weak var newUser: UIStackView!
    @IBOutlet weak var tableView: UITableView!
    
    @IBOutlet weak var add: UIBarButtonItem!
  
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        self.tableView.delegate = self
        self.tableView.dataSource = self
        user_T.delegate = self
    }
    
    
    
    func textFieldShouldReturn(textField: UITextField) -> Bool {
        
        user_T.resignFirstResponder()
        
        if user_T.text?.isEmpty == false
        {
            saveDataToTable(user_T.text!, speed: 0)
        }
        fetchData()
        tableView.reloadData()
        
        return true
    }

    override func touchesBegan(touches: Set<UITouch>, withEvent event: UIEvent?) {
         user_T.resignFirstResponder()
         self.view.endEditing(true)
        
        if user_T.text?.isEmpty == false
        {
            saveDataToTable(user_T.text!, speed: 0)
        }
        newUser.hidden = true
        tableView.hidden = false
        fetchData()
        tableView.reloadData()
        
    }
    
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    override func viewWillAppear(animated: Bool) {
        
        newUser.hidden = true
        
        fetchData()
        newUser.hidden = true
        tableView.hidden = false
        
        tableView.reloadData()
        

    }
    
    @IBAction func addUser(sender: AnyObject) {
        
        newUser.hidden = false
        user_T.text = ""
        tableView.hidden = true

    }
    
    
     func fetchData()
    {
        let appDelegate = UIApplication.sharedApplication().delegate as! AppDelegate
        let context =  appDelegate.managedObjectContext
        
        let fetch = NSFetchRequest(entityName: "Users")
        fetch.resultType = .DictionaryResultType
        fetch.propertiesToFetch = ["userName"]
        fetch.propertiesToGroupBy = ["userName"]
        let sort = NSSortDescriptor(key: "userName", ascending: false)
        
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
        return "Current Users :"
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
        return cell
    }
    
    override func prepareForSegue(segue: UIStoryboardSegue?, sender: AnyObject?) {
        let defaults = NSUserDefaults.standardUserDefaults()
        
        defaults.setObject(selectedUser, forKey: "currentUser")
    }
    
    func tableView(tableView: UITableView, didSelectRowAtIndexPath indexPath: NSIndexPath) {
        selectedUser = (tableView.cellForRowAtIndexPath(indexPath))!.textLabel!.text!
        print(selectedUser)
        self.performSegueWithIdentifier("back", sender: self)
    }
    
    func saveDataToTable(user:String, speed:Int)
    {
        let appDelegate = UIApplication.sharedApplication().delegate as! AppDelegate
        let context =  appDelegate.managedObjectContext
        let newManagedObject = NSEntityDescription.insertNewObjectForEntityForName("Users", inManagedObjectContext: context)
        
        let time = NSDate()
        
        newManagedObject.setValue(user, forKey: "userName")
        newManagedObject.setValue(speed, forKey: "speed")
        newManagedObject.setValue(time, forKey: "timeStamp")
        
        // Save the context.
        do
        {
            try context.save()
        } catch
        {
            abort()
        }
        
    }

}


