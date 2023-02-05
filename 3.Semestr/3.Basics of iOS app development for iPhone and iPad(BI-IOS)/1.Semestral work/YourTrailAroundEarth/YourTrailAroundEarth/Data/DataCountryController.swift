//
//  DataCountryController.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 04.02.2023.
//

import CoreData

final class DataCountryController: ObservableObject {
    let container = NSPersistentContainer(name: "CountryModel")
    
    init() {
        container.loadPersistentStores { description, error in
            if let error = error {
                print("Core data failed to load: \(error.localizedDescription)")
            }
        }
    }
}
