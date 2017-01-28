//
//  FirstViewController.swift
//  Assignment_4_Amey_Parab
//
//  Created by Parab, Amey on 4/20/16.
//  Copyright © 2016 Parab, Amey. All rights reserved.
//

import UIKit
import CoreData

class FirstViewController: UIViewController , UITextFieldDelegate, NSFetchedResultsControllerDelegate{

    @IBOutlet weak var new: UIStackView!
    @IBOutlet weak var entry: UIView!
    @IBOutlet weak var welcome_T: UILabel!
    @IBOutlet weak var wps_T: UILabel!
    @IBOutlet weak var word_L: UILabel!
    
    @IBOutlet weak var wps_S: UISlider!
    var user: String = "" // Current User
    
    var timer = NSTimer()
    
    var counter = 0
    
    var defaultSpeed:String = ""
    var delay:String = ""
    var para :[String] = []
    var paraData:String = ""
    var s = ""
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
        let defaults = NSUserDefaults.standardUserDefaults()
        
        //Set App Defaults
        if (defaults.stringForKey("speed") == nil){
            defaults.setObject(20, forKey: "speed")
        }else{
            defaultSpeed = defaults.stringForKey("speed")!
        }
        
        if (defaults.stringForKey("delay") == nil){
            defaults.setObject(2, forKey: "delay")
        }else{
            delay = defaults.stringForKey("delay")!
        }
        
        // Set Current User
        if (defaults.stringForKey("currentUser") != nil){
            user = defaults.stringForKey("currentUser")!
        }else{
            askForUserName()
            user = s
            defaults.setObject(user, forKey: "currentUser")
        }
        
        
        welcome_T.text = "Welcome" + "  " + user + " !"
        wps_S.value = Float(defaultSpeed)!
          wps_T.text = String(Int(wps_S.value))
    }
    
    override func viewWillAppear(animated: Bool) {
        
        let defaults = NSUserDefaults.standardUserDefaults()
        
        //Set App Defaults
        if (defaults.stringForKey("speed") == nil){
            defaults.setObject(20, forKey: "speed")
        }else{
            defaultSpeed = defaults.stringForKey("speed")!
        }
        
        if (defaults.stringForKey("delay") == nil){
            defaults.setObject(2, forKey: "delay")
        }else{
            delay = defaults.stringForKey("delay")!
        }
        
        // Set Current User
        if (defaults.stringForKey("currentUser") != nil){
            user = defaults.stringForKey("currentUser")!
        }else{
            askForUserName()
            user = s
            defaults.setObject(user, forKey: "currentUser")
        }
        
        welcome_T.text = "Welcome" + "  " + user + " !"
        wps_S.value = Float(defaultSpeed)!
          wps_T.text = String(Int(wps_S.value))
        
    }
    
    @IBAction func start(sender: UIButton)
    {
        let interval = calculateInterval()
        
        print(interval)
        if !delay.isEmpty
        {
            sleep(UInt32(delay)!)
        }
        
        counter = 0
        
        if let path = NSBundle.mainBundle().pathForResource("data", ofType: "txt")
        {
        if let text = try? String(contentsOfFile: path, encoding: NSUTF8StringEncoding)
        {
            para = text.componentsSeparatedByString("~~")
            paraData = para[Int(arc4random_uniform(UInt32(para.count)))]
        }
        }
        // Starting Timer to display word
        timer = NSTimer.scheduledTimerWithTimeInterval(interval, target: self, selector: #selector(FirstViewController.displayWords), userInfo: nil, repeats: true)
        
        saveDataToTable(user, speed: Int(Double(wps_T.text!)!))
    }
    
    func displayWords(){
        
        
            //print(path)
            

                //print(text)
                let fileData = paraData.componentsSeparatedByString(" ")
        
                if counter == fileData.count
                {
                    counter = 0
                }else{
                    counter += 1
                }
        
                if(counter < fileData.count)
                {
                    let word = fileData[counter]
                    
                    
                    let loc = Int(word.characters.count / 2)
                    
                    
                    let wordColor = NSMutableAttributedString(string: word)
                    
                    // change the color atribute
                    
                    wordColor.addAttribute(NSForegroundColorAttributeName, value: UIColor.greenColor(), range: NSRange(location: loc, length: 1))
                    word_L.attributedText = wordColor
                }

        
        // code for fetching word from file
        
        
    }
    
    
    @IBAction func stop(sender: UIButton) {
        // Storing USer detaisl in the Core Data
        timer.invalidate()
        
        word_L.text = "Well Played"
    }
    

    
    func calculateInterval() -> Double
    {
        let wpm = Double(wps_T.text!)
        return (60/wpm!)
    }
    
    func storeUserDetails()
    {
        let appDelegate = UIApplication.sharedApplication().delegate as! AppDelegate
        let context =  appDelegate.managedObjectContext
        let newManagedObject = NSEntityDescription.insertNewObjectForEntityForName("UserDetails", inManagedObjectContext: context)
        
        var speed:Int = 0
        if !(wps_T.text?.isEmpty)!{
            speed = Int(wps_T.text!)!
        }
        newManagedObject.setValue(user, forKey: "username")
        newManagedObject.setValue(speed, forKey: "speed")
        newManagedObject.setValue(NSDate(), forKey: "dateTime")
        
        // Save the context.
        do
        {
            try context.save()
        }
        catch
        {
            abort()
        }
        
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
    
    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    

    @IBAction func slider(sender: AnyObject) {
        wps_T.text = String(Int(wps_S.value))
        
    }
    
    func askForUserName()
    {
         let alert = UIAlertController(title: "New User", message: "User Name", preferredStyle: UIAlertControllerStyle.Alert)
        
        let loginAction = UIAlertAction(title: "Done", style: .Default) { (_) in
            
            let name = alert.textFields![0] as UITextField
            
            if name.text! == "" {
                
                self.s = "default"
            }else
            {
                self.s = name.text!
            }
        }
        
        alert.addTextFieldWithConfigurationHandler { (textField) in
            textField.placeholder = "User Name"
        }
        
        alert.addAction(loginAction)
        dispatch_async(dispatch_get_main_queue(), {
            self.presentViewController(alert, animated: true, completion: nil)
            
            let name = alert.textFields![0] as UITextField
            
            if name.text! == "" {
                
                self.s = "default"
            }else
            {
                self.s = name.text!
            }
        })
       
    }

    
}

