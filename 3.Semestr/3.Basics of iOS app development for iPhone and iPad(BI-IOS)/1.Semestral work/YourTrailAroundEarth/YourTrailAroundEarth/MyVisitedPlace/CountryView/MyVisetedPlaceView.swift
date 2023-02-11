//
//  MyVisetedPlaceView.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 01.02.2023.
//

import SwiftUI

struct MyVisetedPlaceView: View {
    
    @State private var showingAddScreen = false
    
    @State private var showReview = false
    
    @State private var showingEditScreen = false
    
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
                                HStack {
                                    Text(country.flag ?? "")
                                    Text(country.name ?? "")
                                        .fontWeight(.heavy)
                                }
                                
                                Text("Continent: \(country.continent ?? "")")
                                
                                Text("Capital: \(country.capital ?? "")")
                                
                                Text("Language: \(country.language ?? "")")
                                
                                HStack {
                                    Text("Currency: ")
                                    Text((country.currency ?? "") + "(\(country.currencySymbol ?? ""))")
                                }
                                
                                NavigationLink(destination: MyVisitedCityView(keyName: "title", letter: "S", country: country)) {
                                    Image(country.countryCode ?? "NotCountryPicture")
                                        .resizable()
                                        .frame(width: 300, height: 200)
                                        .clipShape(Rectangle())
                                }
                                .buttonStyle(BorderlessButtonStyle())
                                
                                Button("Show review:") {
                                    showReview.toggle()
                                }
                                .buttonStyle(BorderlessButtonStyle())

                                if(showReview) {
                                    Text(country.review ?? "")
                                }
                                
                                Text("Rating: \(String(country.rating))")
                            }
                            .swipeActions {
                                Button(action: {
                                    deleteCoreDataCountries(country: country)
                               }) {
                                   Text("Delete")
                                       .background(Color.red)
                               }
                               .tint(Color.red)
                                
                                Button {
                                    showingEditScreen.toggle()
                                } label: {
                                    Text("Edit")
                                }
                                .tint(Color.blue)
                            }
                            .sheet(isPresented: $showingEditScreen) {
                                EditNewVisitedCountryView(country: country)
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
    
    private func editCoreDataCountries() {
        try? moc.save()
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
