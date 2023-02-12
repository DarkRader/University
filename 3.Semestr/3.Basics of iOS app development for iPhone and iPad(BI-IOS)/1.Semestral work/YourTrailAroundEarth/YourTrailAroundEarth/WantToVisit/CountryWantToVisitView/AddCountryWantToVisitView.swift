//
//  AddCountryWantToVisitView.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 02.02.2023.
//

import MapKit
import SwiftUI

struct AddCountryWantToVisitView: View {
    @State private var countryModule: CountryModule?
    
    @State private var flag = ""
    @State private var name = ""
    @State private var countryName = "AC"
    
    @Environment(\.managedObjectContext) private var moc
    
    @Environment(\.dismiss) private var dismiss
    
    var body: some View {
        NavigationView {
            Form {
                
                Section("Basic information") {
                    Picker("Choose country", selection: $countryName) {
                        ForEach(NSLocale.isoCountryCodes, id: \.self) { countryCode in
                            HStack {
                                Text(countryFlag(countryCode) + (Locale.current.localizedString(forRegionCode: countryCode) ?? "") + "(\(countryCode))")
                            }
                        }
                    }
                }
                
                Section {
                    Button("Save") {
                        let countryFullName = Locale.current.localizedString(forRegionCode: countryName) ?? ""
                        self.fetchCountryInfo(address: countryFullName)
                        
                        dismiss()
                    }
                }
            }
            
        }
        .navigationTitle("Add Country")
    }
    
    private func fetchCountryInfo(address: String) {
        
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
                    
                    let country = CoreDataCountryWant(context: moc)
                    
                    country.id = UUID().uuidString
                    country.countryCode = countryName
                    country.name = Locale.current.localizedString(forRegionCode: countryName) ?? ""
                    country.language = Locale.current.localizedString(forLanguageCode: countryName) ?? "Not found"
                    country.capital = self.countryModule?.data[0].country_module.capital ?? ""
                    country.flag = countryFlag(countryName)
                    country.continent = self.countryModule?.data[0].continent ?? ""
                    country.currency = self.countryModule?.data[0].country_module.currencies[0].name ?? ""
                    country.currencySymbol = self.countryModule?.data[0].country_module.currencies[0].symbol ?? ""
                
                do {
                    try moc.save()
                } catch {
                    print("ERROR SAVING TO CORE DATA:",
                          error.localizedDescription)
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
    
    func countryFlag(_ countryCode: String) -> String {
      String(String.UnicodeScalarView(countryCode.unicodeScalars.compactMap {
        UnicodeScalar(127397 + $0.value)
      }))
    }
    
    private func saveToFileSystem(countries: [CountryWantToVisit]) {
        let documentDirectory = FileManager.default.urls(
            for: .documentDirectory,
            in: .userDomainMask
        ).first
        let url = documentDirectory?.appendingPathExtension(CountryWantSave.url)
        let data = try? JSONEncoder().encode(countries)
        
        if let url = url, let data = data {
            do {
                try data.write(to: url)
            } catch {
                print("COUNTRIES SAVE ERROR:", error.localizedDescription)
            }
        }
    }
    
    private func storeInUserDefaults(countries: [CountryWantToVisit]) {
        UserDefaults.standard.set(
            try? JSONEncoder().encode(countries),
            forKey: CountryWantSave.userDefaultsKey
        )
    }
}

struct AddCountryWantToVisitView_Previews: PreviewProvider {
    static var previews: some View {
        AddCountryWantToVisitView()
            .preferredColorScheme(.light)
        AddCountryWantToVisitView()
            .preferredColorScheme(.dark)
    }
}
