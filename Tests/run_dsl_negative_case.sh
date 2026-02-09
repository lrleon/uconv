#!/usr/bin/env bash
set -euo pipefail

if [[ $# -ne 4 ]]; then
  echo "Usage: run_dsl_negative_case.sh <gen_units> <fixture> <output_dir> <expected_message>" >&2
  exit 2
fi

gen_units="$1"
fixture="$2"
output_dir="$3"
expected_message="$4"

tmp_log="$(mktemp)"
cleanup() {
  rm -f "${tmp_log}"
}
trap cleanup EXIT

set +e
ruby "${gen_units}" "${fixture}" "${output_dir}" >"${tmp_log}" 2>&1
status=$?
set -e

if [[ ${status} -eq 0 ]]; then
  echo "Expected DSL generation to fail for fixture: ${fixture}" >&2
  cat "${tmp_log}" >&2
  exit 1
fi

if ! grep -Fq "${expected_message}" "${tmp_log}"; then
  echo "Expected error message not found: ${expected_message}" >&2
  cat "${tmp_log}" >&2
  exit 1
fi

exit 0
