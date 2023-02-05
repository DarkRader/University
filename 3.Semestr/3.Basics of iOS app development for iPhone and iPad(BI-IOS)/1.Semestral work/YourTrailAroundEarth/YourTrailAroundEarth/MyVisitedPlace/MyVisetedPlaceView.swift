//
//  MyVisetedPlaceView.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 01.02.2023.
//

import SwiftUI

struct MyVisetedPlaceView: View {
    
    @State private var showingAddScreen = false
    
    @FetchRequest private var countries: FetchedResults<CoreDataCountry>
    
    @Environment(\.managedObjectContext) private var moc
    
    private var keyName: String
    
    private var letter: String
    
    init(keyName: String, letter: String) {
        self.keyName = keyName
        self.letter = letter
        
        _countries = FetchRequest<CoreDataCountry>(
            sortDescriptors: [
                SortDescriptor(\.rating, order: .reverse),
                SortDescriptor(\.name)
            ]
            
        )
    }
    
    var body: some View {
        NavigationView {
            List {
                ForEach(countries) { country in
                    HStack {
                        VStack(alignment: .leading) {
                            Text(country.name ?? "")
                                .fontWeight(.heavy)
                            
                            Text(country.photo ?? "")
                                .fontWeight(.medium)
                        }
                        
                        Spacer()
                        
                        Text(String(country.rating))
                    }
                }
                .onDelete(perform: deleteCoreDataCountries)
            }
            .navigationTitle("Visited countries")
            .toolbar {
                ToolbarItem(placement: .navigationBarTrailing) {
                    Button {
                        showingAddScreen.toggle()
                    } label: {
                        Label("Add a new country", systemImage: "plus")
                    }
                }
                
                ToolbarItem(placement: .navigationBarLeading) {
                    EditButton()
                }
            }
        }
        .sheet(isPresented: $showingAddScreen) {
            AddNewVisitedCountryView()
        }
    }
    
    private static func loadCountriesFromFileSystem() -> [Country] {
        let documentDirectory = FileManager.default.urls(
            for: .documentDirectory,
            in: .userDomainMask
        ).first
        let url = documentDirectory?.appendingPathExtension(CountrySave.url)
        
        guard let url = url else { return [] }
        
        do {
            let countriesData = try Data(contentsOf: url)
            
            do {
                let countries = try JSONDecoder().decode([Country].self, from: countriesData)
                return countries
            } catch {
                print("COUNTRIES DECODING ERROR:", error.localizedDescription)
            }
        } catch {
            print("COUNTRIES LOADING ERROR:", error.localizedDescription)
        }
        
        return []
    }
    
    private static func loadCountriesFromUserDefaults() -> [Country] {
        guard
            let countriesData = UserDefaults.standard.data(forKey: CountrySave.userDefaultsKey)
        else { return [] }
        
        do {
            let countries = try JSONDecoder().decode([Country].self, from: countriesData)
            return countries
        } catch {
            print("COUNTRIES DECODING ERROR:", error.localizedDescription)
        }
        
        return []
    }

    private func deleteCoreDataCountries(at offsets: IndexSet) {
        for offset in offsets {
            let country = countries[offset]
            moc.delete(country)
        }
        
        try? moc.save()
    }
    
}

struct MyVisetedPlaceView_Previews: PreviewProvider {
    static var previews: some View {
        MyVisetedPlaceView(keyName: "title", letter: "S")
    }
}
