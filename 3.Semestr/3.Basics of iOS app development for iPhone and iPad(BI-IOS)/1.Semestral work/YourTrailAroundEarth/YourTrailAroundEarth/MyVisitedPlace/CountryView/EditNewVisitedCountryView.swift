//
//  EditNewVisitedCountryView.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 11.02.2023.
//

import SwiftUI

struct EditNewVisitedCountryView: View {
    
    private var country: CoreDataCountry
    
    @State private var language = ""
    @State private var rating = 5
    @State private var review = ""
    
    @Environment(\.dismiss) private var dismiss
    
    @Environment(\.managedObjectContext) private var moc
    
    init(country: CoreDataCountry) {
        self.country = country
    }
    
    var body: some View {
        NavigationView {
            Form {
               
                if country.language == "Not found" {
                    Section("You can change language in this country") {
                        TextEditor(text: $language)
                    }
                }
                
                Section("My old review") {
                    Text(country.review ?? "")
                }
                
                Section("My review") {
                    TextEditor(text: $review)
                        .font(.system(.body))
                        .frame(height: max(100,20))
                        .cornerRadius(10.0)
                        .shadow(radius: 1.0)
                    
                    Picker("Rating", selection: $rating) {
                        ForEach(0..<11) {
                            Text(String($0))
                        }
                    }
                }
                
                Section {
                    Button("Save") {
                        
                        if language != "" {
                            country.language = language
                        }
                        
                        if review != "" {
                            country.review = review
                        }

                        country.rating = Int16(rating)
                        
//                        do {
//                            try? moc.save(country)
//                        } catch {
//                            print("ERROR UPDATE TO CORE DATA:",
//                                  error.localizedDescription)
//                        }
                        
                        dismiss()
                    }
                }
                
            }
            .toolbar(.hidden, for: .tabBar)
        }
    }
}

struct EditNewVisitedCountryView_Previews: PreviewProvider {
    static var previews: some View {
        EditNewVisitedCountryView(country: CoreDataCountry())
    }
}
