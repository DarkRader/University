//
//  AddNewVisitedPlaceView.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 09.02.2023.
//

import SwiftUI

struct AddNewVisitedPlaceView: View {
    
    @State private var countryModule: CountryModule?
    
    @Binding var showError: Bool
    
    @State private var name = ""
    @State private var review = ""
    @State private var rating = 5
    
    @Environment(\.managedObjectContext) private var moc
    
    @Environment(\.dismiss) private var dismiss
    
    private var city: CoreDataCity
    
    init(showError: Binding<Bool>, city: CoreDataCity) {
        self._showError = showError
        self.city = city
    }
    
    var body: some View {
        NavigationView {
            Form {
                
                Section("Find city on map") {
                    NavigationLink(destination: ContentViewMap(startLocation: city.name ?? "", startDelta: 0.5, suitableDelta: 0.01)) {
                        Text("View places in the city on the map")
                    }
                }
                
                Section("Basic information") {
                    TextField(
                        "Name of the place",
                        text: $name
                    )
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
                            //Add a new place
                            self.fetchCountryInfo(address: name)
                            
//                            let place = CoreDataPlace(context: moc)
//                            place.id = UUID().uuidString
//                            place.origin = city
//                            place.name = name
//                            place.rating = Int16(rating)
//                            place.review = review
//
//                            do {
//                                try moc.save()
//                            } catch {
//                                print("ERROR SAVING TO CORE DATA:", error.localizedDescription)
//                            }
                            
                            dismiss()
                        }
                    }
                }
                
            }
            .navigationTitle("Add Place")
        }
    
    func fetchCountryInfo(address: String) {

        let apiKey = "92d0989cebd26dea67f59db3a280d7a6"
        let endpoint = "http://api.positionstack.com/v1/forward?access_key=\(apiKey)&query=\(address)&country_module=1"
        let encodedEndpoint = endpoint.addingPercentEncoding(withAllowedCharacters: .urlQueryAllowed)

        guard let url = URL(string: encodedEndpoint ?? "") else { return }

        URLSession.shared.dataTask(with: url) { (data, response, error) in
            if let error = error {
                print("Error fetching data: \(error.localizedDescription)")
                return
            }

            guard let data = data else {
                print(error!.localizedDescription)
                return }

//            print(String(data: data, encoding: .utf8) ?? "")

            do {
                let decoder = JSONDecoder()
                let countryModule = try decoder.decode(CountryModule.self, from: data)
                self.countryModule = countryModule
                
                if countryModule.data.isEmpty {
                    print("This place not exist.")
                    showError = true
                } else {

                    if countryModule.data[0].type ?? "" == "locality" || countryModule.data[0].type ?? "" == "country" {
                        print("This is not a place.")
                        showError = true
                    } else if countryModule.data[0].locality ?? "" == city.name {
                        print(countryModule.data[0].locality ?? "")
                        print(city.name ?? "")
                        print("This place is not located in this city")
                        showError = true
                    } else {

                        let place = CoreDataPlace(context: moc)

                        place.id = UUID().uuidString
                        place.origin = city
                        place.name = name
                        place.review = review
                        place.rating = Int16(rating)
                        
                        place.street = self.countryModule?.data[0].street ?? "Not found."
                        place.number = self.countryModule?.data[0].number ?? "Not found."
                        place.postal_code = self.countryModule?.data[0].postal_code ?? "Not found."
                        
                        place.type = self.countryModule?.data[0].type ?? "Not found."

                        do {
                            try moc.save()
                        } catch {
                            print("ERROR SAVING TO CORE DATA:",
                                  error.localizedDescription)
                        }
                    }
                }
                
                print("Success...")
            } catch let DecodingError.dataCorrupted(context) {
                print(context)
            } catch let DecodingError.keyNotFound(key, context) {
                print("Key '\(key)' not found:", context.debugDescription)
                print("codingPath:", context.codingPath)
            } catch let DecodingError.valueNotFound(value, context) {
                print("Value '\(value)' not found:", context.debugDescription)
                print("codingPath:", context.codingPath)
            } catch let DecodingError.typeMismatch(type, context)  {
                print("Type '\(type)' mismatch:", context.debugDescription)
                print("codingPath:", context.codingPath)
            } catch {
                print("error: ", error)
            }
        }.resume()
    }
    
    private func saveToFileSystem(places: [Place]) {
        let documentDirectory = FileManager.default.urls(
            for: .documentDirectory,
            in: .userDomainMask
        ).first
        let url = documentDirectory?.appendingPathExtension(PlaceSave.url)
        let data = try? JSONEncoder().encode(places)
        
        if let url = url, let data = data {
            do {
                try data.write(to: url)
            } catch {
                print("PLACES SAVE ERROR:", error.localizedDescription)
            }
        }
    }
    
    private func storeInUserDefaults(places: [Place]) {
        UserDefaults.standard.set(
            try? JSONEncoder().encode(places),
            forKey: PlaceSave.userDefaultsKey
        )
    }
}

struct AddNewVisitedPlaceView_Previews: PreviewProvider {
    
    @State static var showError = false
    
    static var previews: some View {
        AddNewVisitedPlaceView(showError: $showError, city: CoreDataCity())
    }
}
