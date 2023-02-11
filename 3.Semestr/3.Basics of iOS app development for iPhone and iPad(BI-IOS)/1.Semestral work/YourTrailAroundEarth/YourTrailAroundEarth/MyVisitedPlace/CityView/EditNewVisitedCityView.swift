//
//  EditNewVisitedCityView.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 11.02.2023.
//

import SwiftUI

struct EditNewVisitedCityView: View {
    
    private var city: CoreDataCity
    
    @State private var rating = 5
    @State private var review = ""
    
    @Environment(\.dismiss) private var dismiss
    
    @Environment(\.managedObjectContext) private var moc
    
    init(city: CoreDataCity) {
        self.city = city
    }
    
    var body: some View {
        NavigationView {
            Form {
                Section("My old review") {
                    Text(city.review ?? "")
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
                        
                        if review != "" {
                            city.review = review
                        }

                        city.rating = Int16(rating)
                        
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

struct EditNewVisitedCityView_Previews: PreviewProvider {
    static var previews: some View {
        EditNewVisitedCityView(city: CoreDataCity())
    }
}
