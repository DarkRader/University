//
//  YourTrailAroundEarthApp.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 01.02.2023.
//

import SwiftUI

@main
struct YourTrailAroundEarthApp: App {
    @StateObject private var dataCountryController = DataCountryController()
    @StateObject private var dataCityController = DataCityController()
    
    var body: some Scene {
        WindowGroup {
            ContentView()
                .environment(\.managedObjectContext, dataCountryController.container.viewContext)
                .environment(\.managedObjectContext, dataCityController.container.viewContext)
        }
    }
}
