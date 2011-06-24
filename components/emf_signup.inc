<?php

/**
 * Implementation of _webform_defaults_component(). 
 */
function _webform_defaults_emf_signup() {
  return array(
    'name' => '',
    'form_key' => NULL,
    'mandatory' => 0,
    'pid' => 0,
    'weight' => 0,
    'extra' => array(
  		'lists' => array(),
  		'email_field' => NULL,
      'description' => '',
    ),
  );
}

/**
 * Implementation of _webform_edit_component().
 */
function _webform_edit_emf_signup($component) {
  $form = array();

  $lists = array();
  foreach (emf_db_get_lists(TRUE) as $lid => $list) {
  	$lists[$lid] = sprintf('%s (%d: %s)', $list->name_action_clean, $lid, $list->name_clean);
  }
  $form['extra']['lists'] = array(
  	'#type' => 'checkboxes',
    '#title' => t('Lists'),
		'#options' => $lists, 
    '#default_value' => $component['extra']['lists'],
    '#description' => t('Select the lists submitters should be able to sign up for. Not selecting any lists allows for signup for all lists.'),
    '#weight' => 0,
    '#required' => FALSE,
	);
	
	$email_fields = array();
	$result = db_query('SELECT cid, form_key, name FROM {webform_component} WHERE type = "email" AND nid = %d ORDER BY weight, name', $component['nid']);
	while ($c = db_fetch_array($result)) {
		$email_fields[$c['cid']] = sprintf('%s (%s)', $c['name'], $c['form_key']);
	}
	$form['extra']['email_field'] = array(
  	'#type' => 'radios',
    '#title' => t('Email field'),
		'#options' => $email_fields, 
    '#default_value' => (isset($component['extra']['email_field'])) ? $component['extra']['email_field'] : array_shift(array_keys($email_fields)),
    '#description' => t('Select the field which represents the email which should be signed up'),
    '#weight' => 0,
    '#required' => TRUE,
	);

  return $form;
}

/**
 * Implementation of _webform_render_component().
 */
function _webform_render_emf_signup($component, $value = NULL) {
	$lists = array();
	foreach ($component['extra']['lists'] as $lid => $selected) {
		if ($selected &&
				$list = _emf_webform_get_list($lid)) {
			$lists[$lid] = $list->name_action_clean;
		}
	}
  
  $form_item = array(
    '#type' => 'checkboxes',
  	'#options' => $lists,
  	'#title' => ($component['extra']['title_display'] == 'none') ? NULL : $component['name'],
    '#required' => $component['mandatory'],
    '#weight' => $component['weight'],
    '#description'   => _webform_filter_descriptions($component['extra']['description']),
    '#default_value' => array($component['value']),
    '#prefix' => '<div class="webform-component-'. $component['type'] .'" id="webform-component-'. $component['form_key'] .'">',
    '#suffix' => '</div>',
  );

  return $form_item;
}

/**
 * Implementation of _webform_theme_component().
 */
function _webform_theme_emf_signup() {
  return array(
    'webform_display_emf_signup' => array(
      'arguments' => array('element' => NULL),
    ),
  );
}

/**
 * Implementation of _webform_submit_component().
 */
function _webform_submit_emf_signup($component, $value) {
  return array_values(array_filter($value));
}


/**
 * Implementation of _webform_display_component().
 */
function _webform_display_emf_signup($component, $value, $format = 'html') {
	return array(
    '#title' => $component['name'],
    '#weight' => $component['weight'],
    '#theme' => 'webform_display_emf_signup',
    '#theme_wrappers' => $format == 'html' ? array('webform_element', 'webform_element_wrapper') : array('webform_element_text'),
    '#post_render' => array('webform_element_wrapper'),
    '#format' => $format,
    '#value' => (array) $value,
    '#webform_component' => $component,
  );
	
}

function theme_webform_display_emf_signup($element) {
  $component = $element['#webform_component'];
	
  //Get the readable names for the lists
	$items = array_map('_emf_webform_get_list', $element['#value']);
	foreach ($items as &$i) {
		$i = $i->name_clean;
	}
  
  if ($element['#format'] == 'html') {
    $output = count($items) > 1 ? theme('item_list', $items) : (isset($items[0]) ? $items[0] : ' ');
  }
  else {
    if (count($items) > 1) {
      foreach ($items as $key => $item) {
        $items[$key] = ' - ' . $item;
      }
      $output = implode("\n", $items);
    }
    else {
      $output = isset($items[0]) ? $items[0] : ' ';
    }
  }

  return $output;
}

function _webform_table_emf_signup($component, $value) {
	$value = array_map('_emf_webform_get_list', $value);
	foreach ($value as &$v) {
		$v = $v->name_clean;
	}
	return implode(', ', $value);
}

function _emf_webform_get_list($lid) {
	static $lists;
	
	if (!isset($lists)) {
		$lists = emf_db_get_lists();
	}	
	
	return $lists[$lid];
}