package cz.cvut.fit.tjv.swordrentalclient.ui;

import cz.cvut.fit.tjv.swordrentalclient.data.PersonClient;
import cz.cvut.fit.tjv.swordrentalclient.data.SwordClient;
import cz.cvut.fit.tjv.swordrentalclient.model.dto.PersonDto;
import cz.cvut.fit.tjv.swordrentalclient.model.dto.SwordDto;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.*;

import javax.validation.Valid;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

@Controller
@RequestMapping("/persons")
public class PersonWebController {
    private final PersonClient personClient;

    private final SwordClient swordClient;

    @Autowired
    public PersonWebController(PersonClient personClient, SwordClient swordClient) {
        this.personClient = personClient;
        this.swordClient = swordClient;
    }


    @GetMapping
    public String list(Model model) {
        model.addAttribute("persons", personClient.readAll());
        return "persons/persons";
    }

    @GetMapping("/person/{id}")
    public String readPerson(@PathVariable Long id, Model model) {
        model.addAttribute("person", personClient.readById(id));
        return "persons/informationPerson";
    }

    @GetMapping("/edit/{id}")
    public String editPerson(@PathVariable Long id, Model model) {
        model.addAttribute("person", personClient.readById(id));
        return "persons/editPerson";
    }

    @PostMapping("/edit/{id}")
    public String editPersonSubmit(@Valid @ModelAttribute("person") PersonDto personDto, BindingResult bindingResult, @PathVariable Long id) {
        if(bindingResult.hasErrors()) {
            return "persons/editPerson";
        } else {
            personClient.update(personDto, id);
            return "redirect:/persons";
        }
    }

    @GetMapping("/add")
    public String addPerson(Model model) {
        model.addAttribute("person", new PersonDto());
        return "persons/addPerson";
    }

    @PostMapping("/add")
    public String addPersonSubmit(@Valid @ModelAttribute("person") PersonDto personDto, BindingResult bindingResult, Model model) {
        if(bindingResult.hasErrors()) {
            return "persons/addPerson";
        } else {
            model.addAttribute("person", personClient.create(personDto));
            return "redirect:/persons";
        }
    }
    @GetMapping("/wish/{personID}")
    public String wish(@PathVariable Long personID, Model model) {
        Set<SwordDto> wishlist = new HashSet<>();
        PersonDto personDto = personClient.readById(personID);

        for (Long id : personDto.getWishList()) {
            wishlist.add(swordClient.readById(id));
        }

        model.addAttribute("wishlist", wishlist);
        model.addAttribute("renter", personID);
        return "persons/wishingSwordsByPerson";
    }

    @GetMapping("/wish/person/{id}/{idSword}")
    public String deleteSwordWish(@PathVariable(name = "id") Long id, @PathVariable(name = "idSword") Long idSword, Model model) {
        PersonDto personDto = personClient.readById(id);
        personDto.getWishList().remove(idSword);
        personDto.getWantedSwordAlert().remove(idSword);

        SwordDto swordDto = swordClient.readById(idSword);
        swordDto.getPeopleWhoWishesForThisSword().remove(id);

        swordClient.update(swordDto, idSword);
        personClient.update(personDto, id);
        return "redirect:/persons/wish/{id}";
    }

    @GetMapping("/wish/addWishSword/{id}")
    public String addWishSword(@PathVariable Long id, Model model) {
        List<Long> unwish = new ArrayList<>();
        PersonDto personDto = personClient.readById(id);
        for (SwordDto sword: swordClient.readAll()) {
            unwish.add(sword.getSwordId());
        }
        for (Long sword: personDto.getWishList()) {
            unwish.remove(sword);
        }
        List<SwordDto> onlyUnwishSword = new ArrayList<>();
        for (Long sword: unwish) {
            onlyUnwishSword.add(swordClient.readById(sword));
        }

        model.addAttribute("swords", onlyUnwishSword);
        model.addAttribute("personID", id);
        return "persons/addWishSword";
    }

    @GetMapping("/wish/addWishSword/add/{id}/{idSword}")
    public String addCertainSword(@PathVariable(name = "id") Long id, @PathVariable(name = "idSword") Long idSword, Model model) {
        PersonDto personDto = personClient.readById(id);
        personDto.getWishList().add(idSword);

        SwordDto swordDto = swordClient.readById(idSword);
        swordDto.getPeopleWhoWishesForThisSword().add(id);

        swordClient.update(swordDto, idSword);
        personClient.update(personDto, id);
        return "redirect:/persons/wish/addWishSword/{id}";
    }

    @GetMapping("/wish/person/notification{personID}")
    public String notification(@PathVariable Long personID, Model model) {
        Set<SwordDto> alert = new HashSet<>();
        PersonDto personDto = personClient.readById(personID);

        for (Long id : personDto.getWantedSwordAlert()) {
            alert.add(swordClient.readById(id));
        }

        model.addAttribute("alert", alert);
        model.addAttribute("renter", personID);
        return "persons/notification";
    }

    @GetMapping("/delete/{id}")
    public String deletePerson(@PathVariable Long id, Model model) {
         personClient.delete(id);
        return "persons/deletePerson";
    }
}
