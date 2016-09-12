//
//  ViewController.swift
//  ArduinoLampControl
//
//  Created by Pablo Lerma Martínez on 12/09/16.
//  Copyright © 2016 Pablo Lerma. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    @IBOutlet private weak var ledLabel: UILabel!
    private let session = NSURLSession.sharedSession()

    var ledState: Bool = false {
        didSet {
            ledLabel.text = "Led is \(ledState ? "ON" : "OFF")"
            let url = ledState ? "http://192.168.1.177/$1" : "http://192.168.1.177/$2"
            session.dataTaskWithURL(NSURL(string: url)!) { (data: NSData?, response: NSURLResponse?, error: NSError?) in
                print(error)
            }.resume()
        }
    }

    override func viewDidLoad() {
        super.viewDidLoad()

        ledState = false
    }

    @IBAction func switchChanged(sender: UISwitch) {
        ledState = sender.on
    }
}
