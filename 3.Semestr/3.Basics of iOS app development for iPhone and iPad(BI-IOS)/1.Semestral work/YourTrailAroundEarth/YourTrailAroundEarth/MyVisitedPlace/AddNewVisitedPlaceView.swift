//
//  AddNewVisitedPlaceView.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 09.02.2023.
//

import SwiftUI

struct AddNewVisitedPlaceView: View {
    
    @State private var name = ""
    @State private var review = ""
    @State private var rating = 5
    
    @Environment(\.managedObjectContext) private var moc
    
    @Environment(\.dismiss) private var dismiss
    
    private var city: CoreDataCity
    
    init(city: CoreDataCity) {
        self.city = city
    }
    
    var body: some View {
        NavigationView {
            Form {
                Section("Basic information") {
                    TextField(
                        "Name of the place",
                        text: $name
                    )
                }
                    
                    Section("My review") {
                        TextEditor(text: $review)
                        
                        Picker("Rating", selection: $rating) {
                            ForEach(0..<11) {
                                Text(String($0))
                            }
                        }
                    }
                    
                    Section {
                        Button("Save") {
                            //Add a new place
                            let place = CoreDataPlace(context: moc)
                            place.id = UUID().uuidString
                            place.origin = city
                            place.name = name
                            place.rating = Int16(rating)
                            place.review = review
                            
                            do {
                                try moc.save()
                            } catch {
                                print("ERROR SAVING TO CORE DATA:", error.localizedDescription)
                            }
                            
                            dismiss()
                        }
                    }
                }
                
            }
            .navigationTitle("Add Place")
        }
    
    private func saveToFileSystem(placies: [Place]) {
        let documentDirectory = FileManager.default.urls(
            for: .documentDirectory,
            in: .userDomainMask
        ).first
        let url = documentDirectory?.appendingPathExtension(PlaceSave.url)
        let data = try? JSONEncoder().encode(placies)
        
        if let url = url, let data = data {
            do {
                try data.write(to: url)
            } catch {
                print("PLACIES SAVE ERROR:", error.localizedDescription)
            }
        }
    }
    
    private func storeInUserDefaults(placies: [Place]) {
        UserDefaults.standard.set(
            try? JSONEncoder().encode(placies),
            forKey: PlaceSave.userDefaultsKey
        )
    }
}

struct AddNewVisitedPlaceView_Previews: PreviewProvider {
    static var previews: some View {
        AddNewVisitedPlaceView(city: CoreDataCity())
    }
}
