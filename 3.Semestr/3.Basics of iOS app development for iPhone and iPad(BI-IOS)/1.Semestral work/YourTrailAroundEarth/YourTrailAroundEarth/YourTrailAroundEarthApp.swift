//
//  YourTrailAroundEarthApp.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 01.02.2023.
//

import SwiftUI

@main
struct YourTrailAroundEarthApp: App {
    @StateObject private var dataController = DataCountryController()
    
    var body: some Scene {
        WindowGroup {
            ContentView()
                .environment(\.managedObjectContext, dataController.container.viewContext)
        }
    }
}
