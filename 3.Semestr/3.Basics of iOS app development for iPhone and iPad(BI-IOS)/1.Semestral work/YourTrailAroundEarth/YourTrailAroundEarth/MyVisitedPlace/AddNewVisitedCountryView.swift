//
//  AddNewVisitedCountryView.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 04.02.2023.
//

import SwiftUI

struct AddNewVisitedCountryView: View {
    
    private let languages = ["English", "Germany", "Czech", "French"]
    
    @State private var flag = ""
    @State private var name = ""
    @State private var language = "English"
    @State private var review = ""
    @State private var rating = 3
    @State private var countryName = "AC"
    
    @Environment(\.managedObjectContext) private var moc
    
    @Environment(\.dismiss) private var dismiss
    
    var body: some View {
        NavigationView {
            Form {
                Section("Basic information") {
                    Picker("Choose country", selection: $countryName) {
                        ForEach(NSLocale.isoCountryCodes, id: \.self) { countryCode in
                              Text(countryFlag(countryCode) + (Locale.current.localizedString(forRegionCode: countryCode) ?? ""))
                        }
                    }
                    
                    Picker("Languages", selection: $language) {
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
                    
                    Text(Locale.current.localizedString(forRegionCode: countryName) ?? "")
                    Text(countryFlag(countryName))
//                    Text(Locale.current.)
//                    Text(Locale.current.localizedString(forLanguageCode: "cy") ?? "")
                }
                
                Section {
                    Button("Save") {
                        let country = CoreDataCountry(context: moc)
                        
                        country.id = UUID().uuidString
                        country.countryCode = countryName
                        country.name = Locale.current.localizedString(forRegionCode: countryName) ?? ""
                        country.rating = Int16(rating)
                        country.language = language
//                        country.language = Locale.current.localizedString(forLanguageCode: countryName) ?? ""
//                        print(Locale.current.localizedString(forLanguageCode: "en") ?? "")
                        country.review = review
//                        print(Locale.canonicalLanguageIdentifier(from: countryName))
//                        country.capital = ""
                        country.flag = countryFlag(countryName)
                        
                        print(getLanguageISO())
                        
                        do {
                            try moc.save()
                        } catch {
                            print("ERROR SAVING TO CORE DATA:",
                                  error.localizedDescription)
                        }
                        
                        dismiss()
                    }
                }
            }
            
        }
        .navigationTitle("Add Country")
    }
    
    func getLanguageISO() -> String {
//        NSLocale.preferredLanguages
//        let locale = Locale.current.localizedString(forRegionCode: countryName)
        let locale = Locale.current
        guard let languageCode = locale.language.languageCode?.identifier,
              let regionCode = locale.language.region?.identifier else {
           return "de_DE"
       }
       return languageCode + "_" + regionCode
     }
    
    func countryFlag(_ countryCode: String) -> String {
      String(String.UnicodeScalarView(countryCode.unicodeScalars.compactMap {
        UnicodeScalar(127397 + $0.value)
      }))
    }
    
    private func saveToFileSystem(countries: [Country]) {
        let documentDirectory = FileManager.default.urls(
            for: .documentDirectory,
            in: .userDomainMask
        ).first
        let url = documentDirectory?.appendingPathExtension(CountrySave.url)
        let data = try? JSONEncoder().encode(countries)
        
        if let url = url, let data = data {
            do {
                try data.write(to: url)
            } catch {
                print("COUNTRIES SAVE ERROR:", error.localizedDescription)
            }
        }
    }
    
    private func storeInUserDefaults(countries: [Country]) {
        UserDefaults.standard.set(
            try? JSONEncoder().encode(countries),
            forKey: CountrySave.userDefaultsKey
        )
    }
}

struct AddNewVisitedCountryView_Previews: PreviewProvider {
    static var previews: some View {
        AddNewVisitedCountryView()
    }
}
