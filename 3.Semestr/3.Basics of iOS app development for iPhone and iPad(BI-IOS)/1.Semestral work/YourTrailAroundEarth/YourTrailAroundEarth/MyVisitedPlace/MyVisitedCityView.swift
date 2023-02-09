//
//  MyVisitedCityView.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 05.02.2023.
//

import SwiftUI

struct MyVisitedCityView: View {
    
    @State private var showingAddScreen = false
    
    @State private var showReview = false
    
    @FetchRequest private var cities: FetchedResults<CoreDataCity>
    
    @Environment(\.managedObjectContext) private var moc
    
    private var keyName: String
    
    private var letter: String
    
    private var country: CoreDataCountry
    
    init(keyName: String, letter: String, country: CoreDataCountry) {
        self.keyName = keyName
        self.letter = letter
        self.country = country
        
        
        _cities = FetchRequest<CoreDataCity>(
            sortDescriptors: [
                SortDescriptor(\.rating, order: .reverse),
                SortDescriptor(\.name)
            ]
            
        )
    }
    
    var body: some View {
        NavigationView {
            List {
                ForEach(country.citiesList, id: \.self) { city in
                    VStack(alignment: .leading) {
                        HStack {
                            Text(city.origin?.name ?? "")
                            Text(city.name ?? "")
                                .fontWeight(.heavy)
                        }
                        Button("Show review:") {
                           showReview.toggle()
                       }
                       .buttonStyle(BorderlessButtonStyle())

                       if(showReview) {
                           Text(city.review ?? "")
                       }

                       Text("Rating: \(String(city.rating))")
                    }
                    
                    
                }
                .onDelete(perform: deleteCoreDataCities)
            }
            .navigationTitle("Visited cities")
            .toolbar(.hidden, for: .tabBar)
            .toolbar {
                ToolbarItem(placement: .navigationBarTrailing) {
                    Button {
                        showingAddScreen.toggle()
                    } label: {
                        Label("Add a new city", systemImage: "plus")
                    }
                }
                
                ToolbarItem(placement: .navigationBarLeading) {
                    EditButton()
                }
            }
        }
        .sheet(isPresented: $showingAddScreen) {
            AddNewVisitedCityView(country: country)
        }
    }
    
    private static func loadCitiesFromFileSystem() -> [City] {
        let documentDirectory = FileManager.default.urls(
            for: .documentDirectory,
            in: .userDomainMask
        ).first
        let url = documentDirectory?.appendingPathExtension(CitySave.url)
        
        guard let url = url else { return [] }
        
        do {
            let citiesData = try Data(contentsOf: url)
            
            do {
                let cities = try JSONDecoder().decode([City].self, from: citiesData)
                return cities
            } catch {
                print("CITIES DECODING ERROR:", error.localizedDescription)
            }
        } catch {
            print("CITIES LOADING ERROR:", error.localizedDescription)
        }
        
        return []
    }
    
    private static func loadCitiesFromUserDefaults() -> [City] {
        guard
            let citiesData = UserDefaults.standard.data(forKey: CitySave.userDefaultsKey)
        else { return [] }
        
        do {
            let cities = try JSONDecoder().decode([City].self, from: citiesData)
            return cities
        } catch {
            print("COUNTRIES DECODING ERROR:", error.localizedDescription)
        }
        
        return []
    }

    private func deleteCoreDataCities(at offsets: IndexSet) {
        for offset in offsets {
            let city = cities[offset]
            moc.delete(city)
        }
        
        try? moc.save()
    }
}

struct MyVisitedCityView_Previews: PreviewProvider {
    static var previews: some View {
        MyVisitedCityView(keyName: "title", letter: "S", country: CoreDataCountry())
    }
}
