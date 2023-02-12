//
//  DataCountryWantController.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 12.02.2023.
//

import CoreData

final class DataCountryWantController: ObservableObject {
    let container = NSPersistentContainer(name: "CountryWantModel")
    
    init() {
        container.loadPersistentStores { description, error in
            if let error = error {
                print("Core data failed to load: \(error.localizedDescription)")
            }
        }
    }
}
