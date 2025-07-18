//
//  CountryWantToVisitView.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 03.02.2023.
//

import SwiftUI

struct CountryWantToVisitView: View {
    @State private var mapAPI = MapAPI()
    
    @State private var showingAddScreen = false
    
    @State private var showMap = false
    
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
                        countryView(for: country)
                        getPositionView(for: country, for: mapAPI)
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
        .sheet(isPresented: $showMap) {
            ShowLocationOnMapView(mapAPI: $mapAPI)
        }
    }
    
    private func getPositionView(for country: CoreDataCountryWant, for mapAPI: MapAPI) -> some View {
       return HStack {
           Button(action: {
               mapAPI.getLocation(address: country.name ?? "", delta: 20)
           }) {
               Image(systemName: "location")
           }
           .buttonStyle(BorderlessButtonStyle())
           
           Button(action: {
               showMap.toggle()
           }) {
               Image(systemName: "mappin.and.ellipse")
           }
           .buttonStyle(BorderlessButtonStyle())
       }
    }
    
    private func countryView(for country: CoreDataCountryWant) -> some View {
        return VStack(alignment: .leading) {
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
            
            Image(uiImage: UIImage(named: country.countryCode ?? "") ?? UIImage(named: "NotCountryPicture")!)
                .resizable()
                .frame(width: 300, height: 200)
                .clipShape(Rectangle())
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
