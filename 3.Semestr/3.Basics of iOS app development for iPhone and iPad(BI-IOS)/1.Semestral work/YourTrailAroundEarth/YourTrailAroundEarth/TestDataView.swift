//
//  TestDataView.swift
//  YourTrailAroundEarth
//
//  Created by DarkRader on 13.02.2023.
//

import SwiftUI

struct TestDataView: View {
    @State private var address = ""
    @State private var countryModule: CountryModule?
    
    var body: some View {
        VStack {
                   TextField("Enter an address", text: $address)
                       .textFieldStyle(RoundedBorderTextFieldStyle())

                   Button(action: {
                       self.fetchCountryInfo(address: self.address)
                   }) {
                       Text("Get Country Info")
                   }

                   if countryModule != nil {
                       VStack {
                           Group {
                               Text(countryModule?.data[0].type ?? "")
                               Text(countryModule?.data[0].name ?? "")
                               Text(countryModule?.data[0].region ?? "")
                           }
                           Group {
                               Text(countryModule?.data[0].street ?? "")
                               Text(countryModule?.data[0].number ?? "")
                               Text(countryModule?.data[0].postal_code ?? "")
                           }
                           Group {
                               Text(countryModule?.data[0].country ?? "")
                               Text(countryModule?.data[0].country_module.flag ?? "")
                               Text(countryModule?.data[0].country_code ?? "")
                               Text(countryModule?.data[0].continent ?? "")
                               Text(countryModule?.data[0].country_module.capital ?? "")
                           }
                           Group {
                               Text(countryModule?.data[0].country_module.currencies[0].name ?? "")
                               Text(countryModule?.data[0].country_module.currencies[0].code ?? "")
                               Text(countryModule?.data[0].country_module.currencies[0].symbol ?? "")
                               Text(Locale.current.localizedString(forLanguageCode: countryModule?.data[0].country_code ?? "") ?? "")
                           }

                       }
                   } else {
                       VStack {
                           Text("Loading...")
                       }
                   }
               }
               .padding()
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

            print(String(data: data, encoding: .utf8) ?? "")

            do {
                let decoder = JSONDecoder()
                let countryModule = try decoder.decode(CountryModule.self, from: data)
                self.countryModule = countryModule
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
}

struct TestDataView_Previews: PreviewProvider {
    static var previews: some View {
        TestDataView()
    }
}
