//
//  MyVisetedPlaceView.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 01.02.2023.
//

import SwiftUI

struct MyVisetedPlaceView: View {
    @State private var mapAPI = MapAPI()
    
    @State private var showingAddScreen = false
    
    @State private var showMap = false
    
    @State private var selectedObject: CoreDataCountry?
    
    @State private var editCountry = CoreDataCountry()
    
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
        NavigationStack {
            List {
                ForEach(countries) { country in
                            VStack(alignment: .leading) {
                                
                                countryView(for: country)
                                getPositionView(for: country, for: mapAPI)                                
                                showReviewView(for: country, for: selectedObject)
                                
                                Text("Rating: \(String(country.rating))")
                            }
                            .swipeActions {
                                Button(action: {
                                    deleteCoreDataCountries(country: country)
                               }) {
                                   Text("Delete")
                               }
                               .tint(Color.red)
                                
                                NavigationLink(destination: EditNewVisitedCountryView(country: country)) {
                                   Text("Edit")
                                }
                                .tint(Color.blue)
                            }
                }
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
            }
        }
        .sheet(isPresented: $showingAddScreen) {
            AddNewVisitedCountryView()
        }
        .sheet(isPresented: $showMap) {
            ShowLocationOnMapView(mapAPI: $mapAPI)
        }
    }
    
    private func showReviewView(for country: CoreDataCountry, for selectedObject: CoreDataCountry?) -> some View {
        return VStack(alignment: .leading) {
            Button(action: {
                self.selectedObject = self.selectedObject == country ? nil : country
            }) {
                Text("Show review:")
            }
            .buttonStyle(BorderlessButtonStyle())
            
            if self.selectedObject == country {
                Text(country.review ?? "")
            }
        }
    }
    
    private func getPositionView(for country: CoreDataCountry, for mapAPI: MapAPI) -> some View {
       return  HStack {
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
    
    private func countryView(for country: CoreDataCountry) -> some View {
        return VStack(alignment: .leading) {
            HStack {
                Text(country.flag ?? "")
                Text(country.name ?? "")
                    .fontWeight(.heavy)
            }
            
            Group {
                Text("Continent: \(country.continent ?? "")")
                Text("Capital: \(country.capital ?? "")")
                Text("Language: \(country.language ?? "")")
            }
            
            HStack {
                Text("Currency:")
                Text((country.currency ?? "") + "(\(country.currencySymbol ?? ""))")
            }
            
            NavigationLink(destination: MyVisitedCityView(keyName: "title", letter: "S", country: country)) {
                Image(uiImage: UIImage(named: country.countryCode ?? "") ?? UIImage(named: "NotCountryPicture")!)
                    .resizable()
                    .frame(width: 300, height: 200)
                    .clipShape(Rectangle())
            }
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
    
    private func deleteCoreDataCountries(country: CoreDataCountry) {
        moc.delete(country)

        try? moc.save()
    }
    
}

struct MyVisetedPlaceView_Previews: PreviewProvider {
    static var previews: some View {
        MyVisetedPlaceView(keyName: "title", letter: "S")
    }
}
