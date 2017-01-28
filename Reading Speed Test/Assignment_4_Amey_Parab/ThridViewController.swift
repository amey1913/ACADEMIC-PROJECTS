//
//  ThridViewController.swift
//  Assignment_4_Amey_Parab
//
//  Created by Parab, Amey on 4/20/16.
//  Copyright © 2016 Parab, Amey. All rights reserved.
//

import UIKit

class ThridViewController: UIViewController, UITextFieldDelegate{

    @IBOutlet weak var speed: UITextField!
    @IBOutlet weak var currUser: UITextField!
    @IBOutlet weak var delay: UITextField!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        speed.delegate = self
        currUser.delegate = self
        delay.delegate = self
        // Do any additional setup after loading the view.
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    override func viewWillAppear(animated: Bool) {
        
        updateFileds()
    }
    
    
    func updateFileds()
    {
        
        let defaults = NSUserDefaults.standardUserDefaults()
        
        if (defaults.stringForKey("speed") != nil){
            speed.text = defaults.stringForKey("speed")
        }
        
        if (defaults.stringForKey("currentUser") != nil){
           currUser.text = defaults.stringForKey("currentUser")
        }
        
        if (defaults.stringForKey("delay") != nil){
           delay.text = defaults.stringForKey("delay")
        }

    }
    
    func textFieldShouldReturn(textField: UITextField) -> Bool {
        let defaults = NSUserDefaults.standardUserDefaults()
        
        if textField == speed && speed.text?.isEmpty == false
        {
             defaults.setObject(speed.text!, forKey: "speed")
        }

        if textField == delay && delay.text?.isEmpty == false
        {
            defaults.setObject(delay.text!, forKey: "delay")
        }
        
        textField.resignFirstResponder()
        return true
    }
    
    override func touchesBegan(touches: Set<UITouch>, withEvent event: UIEvent?) {
        speed.resignFirstResponder()
        currUser.resignFirstResponder()
        delay.resignFirstResponder()
        let defaults = NSUserDefaults.standardUserDefaults()
        
        if speed.text?.isEmpty == false
        {
            defaults.setObject(speed.text!, forKey: "speed")
        }
        
        if delay.text?.isEmpty == false
        {
            defaults.setObject(delay.text!, forKey: "delay")
        }
        
        self.view.endEditing(true)

        
    }

}
