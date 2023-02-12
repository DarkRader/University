//
//  CityWantToVisitView.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 03.02.2023.
//

import SwiftUI

struct CityWantToVisitView: View {
    
    @State private var showingAddScreen = false
    
    @State var showError = false
    
    @FetchRequest private var cities: FetchedResults<CoreDataCityWant>
    
    @Environment(\.managedObjectContext) private var moc
    
    init() {
        _cities = FetchRequest<CoreDataCityWant>(
            sortDescriptors: [
                SortDescriptor(\.name)
            ]
            
        )
    }
    
    var body: some View {
        NavigationStack {
            List {
                ForEach(cities) { city in
                    VStack(alignment: .leading) {
                        HStack {
                            Text(city.flag ?? "")
                            Text(city.country ?? "")
                        }
                        
                        Text(city.name ?? "")
                            .fontWeight(.heavy)
                        
                        Text("Region: \(city.region ?? "")")
                    }
                }
                .onDelete(perform: deleteCoreDataWantCities)
            }
            .navigationTitle("Cities desired to visit")
            .toolbar(.hidden, for: .tabBar)
            .toolbar {
                ToolbarItem(placement: .navigationBarTrailing) {
                    Button {
                        showingAddScreen.toggle()
                    } label: {
                        Label("Add a new city", systemImage: "plus")
                    }
                }
            }
        }
        .sheet(isPresented: $showingAddScreen) {
            AddCityWantToVisitView(showError: $showError)
        }
        .alert(isPresented: $showError) {
            Alert(title: Text("Error"), message: Text("This place is not a city or not exist. Check the city that you wrote"), dismissButton: .default(Text("OK")))
        }
    }
    
    private static func loadCountriesFromFileSystem() -> [CityWantToVisit] {
        let documentDirectory = FileManager.default.urls(
            for: .documentDirectory,
            in: .userDomainMask
        ).first
        let url = documentDirectory?.appendingPathExtension(CityWantSave.url)
        
        guard let url = url else { return [] }
        
        do {
            let citiesData = try Data(contentsOf: url)
            
            do {
                let cities = try JSONDecoder().decode([CityWantToVisit].self, from: citiesData)
                return cities
            } catch {
                print("CITIES DECODING ERROR:", error.localizedDescription)
            }
        } catch {
            print("CITIES LOADING ERROR:", error.localizedDescription)
        }
        
        return []
    }
    
    private static func loadCountriesFromUserDefaults() -> [CityWantToVisit] {
        guard
            let citiesData = UserDefaults.standard.data(forKey: CityWantSave.userDefaultsKey)
        else { return [] }
        
        do {
            let cities = try JSONDecoder().decode([CityWantToVisit].self, from: citiesData)
            return cities
        } catch {
            print("CITIES DECODING ERROR:", error.localizedDescription)
        }
        
        return []
    }
    
    private func deleteCoreDataWantCities(at offsets: IndexSet) {
        for offset in offsets {
            let city = cities[offset]
            moc.delete(city)
        }
        
        try? moc.save()
    }
}

struct CityWantToVisitView_Previews: PreviewProvider {
    static var previews: some View {
        CityWantToVisitView()
    }
}
