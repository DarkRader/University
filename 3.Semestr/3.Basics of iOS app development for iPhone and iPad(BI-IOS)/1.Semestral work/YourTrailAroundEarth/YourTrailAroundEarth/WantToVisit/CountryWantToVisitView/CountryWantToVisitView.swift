//
//  CountryWantToVisitView.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 03.02.2023.
//

import SwiftUI

struct CountryWantToVisitView: View {
    
    @State private var showingAddScreen = false
    
    @FetchRequest private var countries: FetchedResults<CoreDataCountryWant>
    
    @Environment(\.managedObjectContext) private var moc
    
    init() {
        _countries = FetchRequest<CoreDataCountryWant>(
            sortDescriptors: [
                SortDescriptor(\.name)
            ]
            
        )
    }
    
    var body: some View {
        NavigationStack {
            List {
                ForEach(countries) { country in
                    VStack(alignment: .leading) {
                        HStack {
                            Text(country.flag ?? "")
                            Text(country.name ?? "")
                                .fontWeight(.heavy)
                        }
                        
                        Text("Continent: \(country.continent ?? "")")
                        
                        Text("Capital: \(country.capital ?? "")")
                        
                        Text("Language: \(country.language ?? "")")
                        
                        HStack {
                            Text("Currency:")
                            Text((country.currency ?? "") + "(\(country.currencySymbol ?? ""))")
                        }
                        
                        Image(country.countryCode ?? "NotCountryPicture")
                            .resizable()
                            .frame(width: 300, height: 200)
                            .clipShape(Rectangle())
                        
                    }
                }
                .onDelete(perform: deleteCoreDataWantCountries)
            }
            .navigationTitle("Countries desired to visit")
            .toolbar(.hidden, for: .tabBar)
            .toolbar {
                ToolbarItem(placement: .navigationBarTrailing) {
                    Button {
                        showingAddScreen.toggle()
                    } label: {
                        Label("Add a new country", systemImage: "plus")
                    }
                }
            }
        }
        .sheet(isPresented: $showingAddScreen) {
            AddCountryWantToVisitView()
        }
    }
    
    private static func loadCountriesFromFileSystem() -> [CountryWantToVisit] {
        let documentDirectory = FileManager.default.urls(
            for: .documentDirectory,
            in: .userDomainMask
        ).first
        let url = documentDirectory?.appendingPathExtension(CountryWantSave.url)
        
        guard let url = url else { return [] }
        
        do {
            let countriesData = try Data(contentsOf: url)
            
            do {
                let countries = try JSONDecoder().decode([CountryWantToVisit].self, from: countriesData)
                return countries
            } catch {
                print("COUNTRIES DECODING ERROR:", error.localizedDescription)
            }
        } catch {
            print("COUNTRIES LOADING ERROR:", error.localizedDescription)
        }
        
        return []
    }
    
    private static func loadCountriesFromUserDefaults() -> [CountryWantToVisit] {
        guard
            let countriesData = UserDefaults.standard.data(forKey: CountryWantSave.userDefaultsKey)
        else { return [] }
        
        do {
            let countries = try JSONDecoder().decode([CountryWantToVisit].self, from: countriesData)
            return countries
        } catch {
            print("COUNTRIES DECODING ERROR:", error.localizedDescription)
        }
        
        return []
    }
    
    private func deleteCoreDataWantCountries(at offsets: IndexSet) {
        for offset in offsets {
            let country = countries[offset]
            moc.delete(country)
        }
        
        try? moc.save()
    }
}

struct CountryWantToVisitView_Previews: PreviewProvider {
    static var previews: some View {
        CountryWantToVisitView()
    }
}
