package cz.cvut.fit.tjv.swordrentalclient.ui;

import cz.cvut.fit.tjv.swordrentalclient.data.SwordClient;
import cz.cvut.fit.tjv.swordrentalclient.model.dto.SwordDto;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.validation.BindingResult;
import org.springframework.web.bind.annotation.*;

import javax.validation.Valid;

@Controller
@RequestMapping("/swords")
public class SwordWebController {
    private final SwordClient swordClient;

    @Autowired
    public SwordWebController(SwordClient swordClient) {
        this.swordClient = swordClient;
    }

    @GetMapping
    public String list(Model model) {
        model.addAttribute("swords", swordClient.readAll());
        return "swords/swords";
    }

    @GetMapping("/edit/{id}")
    public String editSword(@PathVariable Long id, Model model) {
        model.addAttribute("sword", swordClient.readById(id));
        return "swords/editSword";
    }

    @PostMapping("/edit/{id}")
    public String editSwordSubmit(@Valid @ModelAttribute("sword") SwordDto swordDto, BindingResult bindingResult, @PathVariable Long id) {
        if(bindingResult.hasErrors()) {
            return "swords/editSword";
        } else {
            swordClient.update(swordDto, id);
            return "redirect:/swords";
        }
    }

    @GetMapping("/add")
    public String addSword(Model model) {
        model.addAttribute("sword", new SwordDto());
        return "swords/addSword";
    }

    @PostMapping("/add")
    public String addSwordSubmit(@Valid @ModelAttribute("sword") SwordDto swordDto, BindingResult bindingResult, Model model) {
        if(bindingResult.hasErrors()) {
            return "swords/addSword";
        } else {
            model.addAttribute("sword", swordClient.create(swordDto));
            return "redirect:/swords";
        }
    }

    @GetMapping("/delete/{id}")
    public String deletePlayer(@PathVariable Long id, Model model) {
        swordClient.delete(id);
        return "swords/deleteSword";
    }
}
