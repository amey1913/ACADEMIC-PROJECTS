//
//  IPGen.swift
//  Assignment_3_Amey_Parab
//
//  Created by Parab, Amey on 3/29/16.
//  Copyright © 2016 Parab, Amey. All rights reserved.
//

import Foundation

class IPGen
{
    var ip : String
    var sub : Int
    
    var subnetAddress : String {
        get {
            let onBits = String(count: self.sub, repeatedValue : Character("1"))
            let offBits = String(count: 32 - self.sub, repeatedValue : Character("0"))
            
            let subnetBinaryString = onBits + offBits
            
            let subnet1 = strtoul(subnetBinaryString.substringWithRange(Range(start: subnetBinaryString.startIndex, end: subnetBinaryString.startIndex.advancedBy(8))), nil , 2)
            let subnet2 = strtoul(subnetBinaryString.substringWithRange(Range(start: subnetBinaryString.startIndex.advancedBy(8), end: subnetBinaryString.startIndex.advancedBy(16))), nil , 2)
            let subnet3 = strtoul(subnetBinaryString.substringWithRange(Range(start: subnetBinaryString.startIndex.advancedBy(16), end: subnetBinaryString.startIndex.advancedBy(24))), nil , 2)
            let subnet4 = strtoul(subnetBinaryString.substringWithRange(Range(start: subnetBinaryString.startIndex.advancedBy(24), end: subnetBinaryString.startIndex.advancedBy(32))), nil , 2)
            
            return "\(subnet1).\(subnet2).\(subnet3).\(subnet4)"
        }
    }
    
    init(ip : String, subnetBits: Int){
        self.ip = ip
        self.sub = subnetBits
    }
    
    func rangeOfIps()->[String]{
        
        // Logic for calulation
        let ipArray = self.ip.componentsSeparatedByString(".")
        let subnetArray = subnetAddress.componentsSeparatedByString(".")
        
        let first1 = UInt8(ipArray[0])! & UInt8(subnetArray[0])!
        let first2 = UInt8(ipArray[1])! & UInt8(subnetArray[1])!
        let first3 = UInt8(ipArray[2])! & UInt8(subnetArray[2])!
        let first4 = (UInt8(ipArray[3])! & UInt8(subnetArray[3])!) + 1
        
        let last1 = UInt8(first1 ^ ~UInt8(subnetArray[0])!)
        let last2 = UInt8(first2 ^ ~UInt8(subnetArray[1])!)
        let last3 = UInt8(first3 ^ ~UInt8(subnetArray[2])!)
        let last4 = UInt8(first4 ^ ~UInt8(subnetArray[3])!)
        
        let from = "\(first1).\(first2).\(first3).\(first4)"
        let to = "\(last1).\(last2).\(last3).\(last4)"
        
        print("\(from)       \(to)")
        
        var addressList:[String] = []
        
        var addr = ""
        
        for var i = first1; i <= last1; i++
        {
            for var j = first2; j <= last2; j++
            {
                for var k = first3; k <= last3; k++
                {
                    for var l = first4; l <= last4; l++
                    {
                        addr = "\(i).\(j).\(k).\(l)"
                        addressList.append(addr);
                    }
                }
            }
        }
        
        return addressList
    }
    
}
/*
var obj = IPGen(ip: "192.168.1.0", subnetBits: 26)
var out = obj.rangeOfIps()

for o in out
{
    print(o)
}

*/
