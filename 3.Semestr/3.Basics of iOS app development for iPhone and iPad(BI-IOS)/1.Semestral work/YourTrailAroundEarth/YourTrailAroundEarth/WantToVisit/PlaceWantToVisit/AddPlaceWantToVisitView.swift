//
//  AddPlaceWantToVisitView.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 12.02.2023.
//

import SwiftUI

struct AddPlaceWantToVisitView: View {
    
    @State private var countryModule: CountryModule?
    
    @Binding var showError: Bool
    
    @State private var name = ""
    
    @Environment(\.managedObjectContext) private var moc
    
    @Environment(\.dismiss) private var dismiss
    
    init(showError: Binding<Bool>) {
        self._showError = showError
    }
    
    var body: some View {
        NavigationView {
            Form {
                
                Section("Find city on map") {
                    NavigationLink(destination: ContentViewMap(startLocation: name, startDelta: 0.5, suitableDelta: 0.01)) {
                        Text("View places in the city on the map")
                    }
                }
                
                Section("Basic information") {
                    TextField(
                        "Name of the place",
                        text: $name
                    )
                }
                
                Section {
                    Button("Save") {
                        //Add a new place
                        self.fetchCountryInfo(address: name)
                        
                        dismiss()
                    }
                }
            }
        }
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
                    } else {

                        let place = CoreDataPlaceWant(context: moc)

                        place.id = UUID().uuidString
                        place.name = name
                        
                        place.flag = self.countryModule?.data[0].country_module.flag ?? "Not found"
                        place.country = self.countryModule?.data[0].country ?? "Not found"
                        place.city = self.countryModule?.data[0].locality ?? "Not found"
                        
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
    
    private func saveToFileSystem(places: [PlaceWantToVisit]) {
        let documentDirectory = FileManager.default.urls(
            for: .documentDirectory,
            in: .userDomainMask
        ).first
        let url = documentDirectory?.appendingPathExtension(PlaceWantSave.url)
        let data = try? JSONEncoder().encode(places)
        
        if let url = url, let data = data {
            do {
                try data.write(to: url)
            } catch {
                print("PLACES SAVE ERROR:", error.localizedDescription)
            }
        }
    }
    
    private func storeInUserDefaults(places: [PlaceWantToVisit]) {
        UserDefaults.standard.set(
            try? JSONEncoder().encode(places),
            forKey: PlaceSave.userDefaultsKey
        )
    }
}

struct AddPlaceWantToVisitView_Previews: PreviewProvider {
    
    @State static var showError = false
    
    static var previews: some View {
        AddPlaceWantToVisitView(showError: $showError)
    }
}
