package cz.cvut.fit.tjv.swordrentalclient.ui;

import cz.cvut.fit.tjv.swordrentalclient.data.ContractClient;
import cz.cvut.fit.tjv.swordrentalclient.data.PersonClient;
import cz.cvut.fit.tjv.swordrentalclient.data.SwordClient;
import cz.cvut.fit.tjv.swordrentalclient.model.dto.ContractDto;
import cz.cvut.fit.tjv.swordrentalclient.model.dto.SwordDto;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.*;

import javax.validation.Valid;
import java.util.ArrayList;
import java.util.List;

@Controller
@RequestMapping("/contracts")
public class ContractWebController {
    private final ContractClient contractClient;

    private final PersonClient personClient;

    private final SwordClient swordClient;


    @Autowired
    public ContractWebController(ContractClient contractClient, PersonClient personClient, SwordClient swordClient) {
        this.contractClient = contractClient;
        this.personClient = personClient;
        this.swordClient = swordClient;
    }


    @GetMapping
    public String list(Model model) {
        model.addAttribute("contracts", contractClient.readAll());
        return "contracts/contracts";
    }

    @GetMapping("/person/{id}")
    public String readPerson(@PathVariable Long id, Model model) {
        model.addAttribute("person", personClient.readById(id));
        return "contracts/infoPerson";
    }

    @GetMapping("/sword/{id}")
    public String readSword(@PathVariable Long id, Model model) {
        model.addAttribute("sword", swordClient.readById(id));
        return "contracts/infoSword";
    }

    @GetMapping("/edit/{id}")
    public String editContract(@PathVariable Long id, Model model) {
        model.addAttribute("contract", contractClient.readById(id));
        return "contracts/editContract";
    }

    @PostMapping("/edit/{id}")
    public String editContractSubmit(@Valid @ModelAttribute("contract") ContractDto contractDto, BindingResult bindingResult, @PathVariable Long id) {
        if(bindingResult.hasErrors()) {
            return "contracts/editContract";
        } else {
            contractClient.update(contractDto, id);
            return "redirect:/contracts";
        }
    }

    @GetMapping("/add")
    public String addContract(Model model) {
        List<Long> swordDto = new ArrayList<>();
        for (SwordDto id: swordClient.readAll()) {
            swordDto.add(id.getSwordId());
        }
        for (ContractDto sword: contractClient.readAll()) {
            swordDto.remove(sword.getSword());
        }
        List<SwordDto> objectSword = new ArrayList<>();
        for (Long sword: swordDto) {
            objectSword.add(swordClient.readById(sword));
        }

        model.addAttribute("person", personClient.readAll());
        model.addAttribute("sword", objectSword);
        model.addAttribute("contract", new ContractDto());
        return "contracts/addContract";
    }

    @PostMapping("/add")
    public String addContractSubmit(@Valid @ModelAttribute("contract") ContractDto contractDto, BindingResult bindingResult, Model model) {
        if(bindingResult.hasErrors()) {
            List<Long> swordDto = new ArrayList<>();
            for (SwordDto id: swordClient.readAll()) {
                swordDto.add(id.getSwordId());
            }
            for (ContractDto sword: contractClient.readAll()) {
                swordDto.remove(sword.getSword());
            }
            List<SwordDto> objectSword = new ArrayList<>();
            for (Long sword: swordDto) {
                objectSword.add(swordClient.readById(sword));
            }
            model.addAttribute("person", personClient.readAll());
            model.addAttribute("sword", objectSword);
            return "contracts/addContract";
        } else {
            model.addAttribute("contract", contractClient.create(contractDto));
            return "redirect:/contracts";
        }
    }

    @GetMapping("/delete/{id}")
    public String deletePlayer(@PathVariable Long id, Model model) {
        contractClient.delete(id);
        return "contracts/deleteContract";
    }
}
