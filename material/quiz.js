function toggle_disabled(form_quiz_choices, disable=false, uncheck=false) {
    form_quiz_choices.forEach((item) => {
        let checkbox = item.querySelector("input[type=checkbox]");
        if (uncheck) checkbox.checked = false;
        checkbox.disabled = disable;
    });
}

let style_quiz = document.head.appendChild(document.createElement("style"));
style_quiz.innerHTML = `
input[type=checkbox].wrong-answer + .task-list-indicator::before {
    background-color: #DD1111 !important;
}
`;
let document_addr = document.location.pathname;
let multiple_choice_questions = document.querySelectorAll(".admonition.question.choice");

multiple_choice_questions.forEach((item, k) => {
    let storage_key = document_addr + "/choice-" + k;
    let previous_answer = localStorage.getItem(storage_key);

    let choices_ul = item.querySelector(".task-list");
    let choices_original = item.querySelectorAll(".task-list-item");
    let correct_choice = null;

    choices_ul.remove();

    let form_quiz = document.createElement("form");
    let form_quiz_ul = choices_ul.cloneNode(true);
    let form_quiz_choices = form_quiz_ul.querySelectorAll(".task-list-item");
    form_quiz.appendChild(form_quiz_ul);

    let answer = item.querySelector(".admonition.details");
    answer.remove();
    answer.style.display = "none";
    form_quiz.appendChild(answer);

    toggle_disabled(form_quiz_choices, false, false);

    for (let i = 0; i < choices_original.length; i++) {
        let check_original = choices_original[i].querySelector("input[type=checkbox]");
        let check_quiz = form_quiz_choices[i].querySelector("input[type=checkbox]");
        
        if (check_original.checked) {
            correct_choice = form_quiz_choices[i];
            check_quiz.checked = false;
        }

        
        if (previous_answer === null) {
            form_quiz_choices[i].addEventListener("click", (evt) => {
                if (check_quiz.disabled) return false;
                evt.preventDefault();
                check_quiz.checked = !check_quiz.checked;
                let choice = form_quiz_choices[i];
                
                correct_choice.querySelector("input[type=checkbox]").checked = true;
                if (choice != correct_choice) {
                    check_quiz.classList.add("wrong-answer");
                }

                localStorage[storage_key] = i;

                toggle_disabled(form_quiz_choices, true);
                answer.style.display = "";

                return true;
            });
        } else {
            check_quiz.disabled = true;
        }
    }

    if (previous_answer !== null) {
        correct_choice.querySelector("input[type=checkbox]").checked = true;
        let idx = parseInt(previous_answer);
        if (form_quiz_choices[idx] != correct_choice) {
            let checkbox = form_quiz_choices[idx].querySelector("input[type=checkbox]")
            checkbox.checked = true;
            checkbox.classList.add("wrong-answer");
        }
        answer.style.display = "";
    }

    item.appendChild(form_quiz);
});