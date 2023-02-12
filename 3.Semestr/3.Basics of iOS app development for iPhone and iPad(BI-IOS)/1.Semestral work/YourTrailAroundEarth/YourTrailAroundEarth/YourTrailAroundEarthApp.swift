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
    @StateObject private var dataPlaceController = DataPlaceController()
    @StateObject private var dataCountryWantController = DataCountryWantController()
    @StateObject private var dataCityWantController = DataCityWantController()
    @StateObject private var dataPlaceWantController = DataPlaceWantController()
    
    var body: some Scene {
        WindowGroup {
            ContentView()
                .environment(\.managedObjectContext, dataCountryController.container.viewContext)
                .environment(\.managedObjectContext, dataCityController.container.viewContext)
                .environment(\.managedObjectContext, dataPlaceController.container.viewContext)
                .environment(\.managedObjectContext, dataCountryWantController.container.viewContext)
                .environment(\.managedObjectContext, dataCityWantController.container.viewContext)
                .environment(\.managedObjectContext, dataPlaceWantController.container.viewContext)
        }
    }
}
