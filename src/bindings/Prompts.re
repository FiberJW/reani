type selectOption = {
  title: string,
  value: string,
};

type singleSelectOptions = {
  [@bs.as "type"]
  _type: string,
  name: string,
  message: string,
  choices: array(selectOption),
};

type selectValue = {value: string};

[@bs.module]
external singleSelect: singleSelectOptions => Js.Promise.t(selectValue) =
  "prompts";