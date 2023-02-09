//
//  AddNewVisitedCityView.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 05.02.2023.
//

import SwiftUI

struct AddNewVisitedCityView: View {
    
    private let languages = ["English", "Germany", "Czech", "French"]
    
    @State private var name = ""
    @State private var language = "English"
    @State private var review = ""
    @State private var rating = 5
    
    @Environment(\.managedObjectContext) private var moc
    
    @Environment(\.dismiss) private var dismiss
    
    private var country: CoreDataCountry
    
    init(country: CoreDataCountry) {
        self.country = country
    }
    
    var body: some View {
        NavigationView {
            Form {
                Section("Basic information") {
                    TextField(
                        "Name of the city",
                        text: $name
                    )
                    
                    Picker("Language", selection: $language) {
                        ForEach(languages, id: \.self) {
                            Text($0)
                        }
                    }
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
                        // Add a new city
                        let city = CoreDataCity(context: moc)
                        city.origin = country
                        city.name = name
                        city.flag = language
                        city.rating = Int16(rating)
                        city.review = review

                        
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
        .navigationTitle("Add City")
        
    }
    
    private func saveToFileSystem(cities: [City]) {
        let documentDirectory = FileManager.default.urls(
            for: .documentDirectory,
            in: .userDomainMask
        ).first
        let url = documentDirectory?.appendingPathExtension(CitySave.url)
        let data = try? JSONEncoder().encode(cities)
        
        if let url = url, let data = data {
            do {
                try data.write(to: url)
            } catch {
                print("CITIES SAVE ERROR:", error.localizedDescription)
            }
        }
    }
    
    private func storeInUserDefaults(cities: [City]) {
        UserDefaults.standard.set(
            try? JSONEncoder().encode(cities),
            forKey: CitySave.userDefaultsKey
        )
    }

}

struct AddNewVisitedCityView_Previews: PreviewProvider {
    static var previews: some View {
        AddNewVisitedCityView(country: CoreDataCountry())
    }
}
